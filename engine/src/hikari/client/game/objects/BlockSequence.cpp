#include "hikari/client/game/GameWorld.hpp"
#include "hikari/client/game/events/EventBus.hpp"
#include "hikari/client/game/events/EventData.hpp"
#include "hikari/client/game/events/AudioEventData.hpp"
#include "hikari/client/game/objects/Entity.hpp"
#include "hikari/client/game/objects/Enemy.hpp"
#include "hikari/client/game/objects/BlockSequence.hpp"
#include "hikari/client/game/objects/BlockTiming.hpp"
#include "hikari/core/util/Log.hpp"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

namespace hikari {
    BlockSequence::BlockSequence(const BlockSequenceDescriptor & descriptor, GameWorld & world, int id)
        : GameObject(id)
        , zIndex(0)
        , step(0)
        , timer(0.0f)
        , descriptor(descriptor)
        , world(world)
        , blockEntities()
        , outlineShape()
        , blockRects()
    {
        const auto & bounds = getBounds();

        outlineShape.setSize({
            static_cast<float>(bounds.getWidth()),
            static_cast<float>(bounds.getHeight())
        });

        outlineShape.setPosition({
            static_cast<float>(bounds.getX()),
            static_cast<float>(bounds.getY())
        });

        outlineShape.setFillColor({ 255, 192, 10, 128 });

        const auto & blockPositions = descriptor.getBlockPositions();

        std::for_each(
            std::begin(blockPositions),
            std::end(blockPositions),
            [&](const Point2D<int> & topLeft){
                sf::RectangleShape shape;

                shape.setPosition({
                    static_cast<float>(topLeft.getX()),
                    static_cast<float>(topLeft.getY())
                });

                shape.setSize({
                    16.0f,
                    16.0f
                });

                shape.setFillColor({ 255, 32, 32, 128 });

                blockRects.push_back(shape);

                std::unique_ptr<Enemy> entityUnique = world.spawnEnemy(descriptor.getEntityName());
                std::shared_ptr<Enemy> entityShared(std::move(entityUnique));
                entityShared->setPosition(topLeft.getX(), topLeft.getY());

                blockEntities.push_back(entityShared);
            });


    }

    BlockSequence::~BlockSequence() {
        blockEntities.clear();
    }

    void BlockSequence::onActivated() {
        reset();
    }

    void BlockSequence::onDeactivated() {
        reset();

        for(auto it = std::begin(blockEntities), end = std::end(blockEntities); it != end; it++) {
            auto & entity = *it;

            if(entity) {
                entity->reset();
                entity->setActive(false);
                world.queueObjectRemoval(entity);
            }
        }
    }

    void BlockSequence::update(float dt) {
        if(isActive()) {
            timer += dt;

            const auto & timing = descriptor.getTiming();

            // First we need to hide any entities that are older than they should be.
            for(auto it = std::begin(blockEntities), end = std::end(blockEntities); it != end; it++) {
                auto & entity = *it;

                if(entity && entity->isActive()) {
                    if(entity->getAge() >= descriptor.getMaximumBlockAge()) {
                        entity->reset();
                        entity->setActive(false);
                        world.queueObjectRemoval(entity);
                    }
                }
            }

            if(timer >= descriptor.getSpawnInterval()) {
                timer = 0.0f;

                const BlockTiming & timingStep = timing.at(step);

                for(auto it = std::begin(timingStep.getBlockIndicies()), end = std::end(timingStep.getBlockIndicies()); it != end; it++) {
                    int index = *it;
                    auto & entity = blockEntities[index];

                    blockRects[index].setFillColor({ 32, 255, 32, 196 });

                    if(entity) {
                        entity->setActive(true);
                        entity->setAgeless(false);
                        world.queueObjectAddition(blockEntities[index]);
                    }
                }

                if(timingStep.getBlockIndicies().size()) {
                    if(auto events = eventBus.lock()) {
                        events->triggerEvent(
                            EventDataPtr(
                                new AudioEventData(
                                    AudioEventData::ACTION_PLAY_SAMPLE,
                                    descriptor.getSoundName()
                                )
                            )
                        );
                    }
                }

                step++;
            }

            if(step >= timing.size()) {
                reset();
            }



            // // Check if we want to advance along in the sequence...
            // if(timer >= timingStep.getAtTime()) {
            //     // Process activiations
            //     for(auto it = std::begin(timingStep.getActivations()), end = std::end(timingStep.getActivations()); it != end; it++) {
            //         int id = *it;
            //         auto & entity = blockEntities[id];

            //         blockRects[id].setFillColor({ 32, 255, 32, 196 });

            //         if(entity) {
            //             entity->setActive(true);
            //             world.queueObjectAddition(blockEntities[id]);
            //         }
            //     }

            //     for(auto it = std::begin(timingStep.getDeactivations()), end = std::end(timingStep.getDeactivations()); it != end; it++) {
            //         int id = *it;
            //         auto & entity = blockEntities[id];

            //         blockRects[id].setFillColor({ 255, 32, 32, 128 });

            //         if(entity) {
            //             entity->reset();
            //             entity->setActive(false);
            //             world.queueObjectRemoval(entity);
            //         }
            //     }

            //     if(timingStep.getActivations().size()) {
            //         if(auto events = eventBus.lock()) {
            //             events->triggerEvent(
            //                 EventDataPtr(
            //                     new AudioEventData(
            //                         AudioEventData::ACTION_PLAY_SAMPLE,
            //                         descriptor.getSoundName()
            //                     )
            //                 )
            //             );
            //         }
            //     }

            //     // Advance the step counter
            //     step++;
            // }

            // // We got to the end so reset.
            // if(step >= timing.size()) {
            //     reset();
            // }
        }
    }

    void BlockSequence::reset() {
        step = 0;
        timer = 0.0f;

        // for(auto it = std::begin(blockRects), end = std::end(blockRects); it != end; it++) {
        //     it->setFillColor({ 255, 32, 32, 128 });
        // }
    }

    void BlockSequence::render(sf::RenderTarget &target) {
        // target.draw(outlineShape);

        // for(auto it = std::begin(blockRects), end = std::end(blockRects); it != end; it++) {
        //     target.draw(*it);
        // }
    }

    void BlockSequence::setZIndex(int index) {
        zIndex = index;
    }

    int BlockSequence::getZIndex() const {
        return zIndex;
    }

    const Rectangle2D<int> & BlockSequence::getBounds() const {
        return descriptor.getBounds();
    }

    void BlockSequence::setEventBus(const std::weak_ptr<EventBus> & eventBus) {
        this->eventBus = eventBus;
    }

} // hikari
