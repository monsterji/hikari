#ifndef HIKARI_CORE_GAME_ANIMATOR
#define HIKARI_CORE_GAME_ANIMATOR

#include "hikari/core/Platform.hpp"
#include <memory>
#include <functional>

namespace hikari {

    class Animation;

    class HIKARI_API Animator {
    public:
        typedef std::function<void (const Animation&)> AnimationCallback;

    private:
        bool paused;
        float timeElapsed;
        unsigned int currentFrameIndex;
        const Animation * animation;
        AnimationCallback callback;

        void play(float delta);
        void handleEndOfAnimation();
        float getCurrentFrameDuration() const;

    protected:
        float getTimeElapsed() const;
        unsigned int getCurrentFrameIndex() const;
        const Animation * const getAnimation() const;

    public:
        Animator();
        virtual ~Animator();
        void rewind();
        void pause();
        void unpause();
        const bool isPaused() const;
        virtual void update(float delta);
        void setAnimation(const Animation * animation);
        void setAnimationCallback(const AnimationCallback& callback);
    };

} // hikari

#endif // HIKARI_CORE_GAME_ANIMATOR
