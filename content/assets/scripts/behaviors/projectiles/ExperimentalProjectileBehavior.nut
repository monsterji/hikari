class ExperimentalProjectileBehavior extends ProjectileBehavior {
    counter = 0.0;

    constructor(classConfig = {}) {
        base.constructor(classConfig);
    }

    function update(dt) {
        counter += dt;

        if(counter >= 0.25) {
            ::log("WOMP!!!");
            counter -= 0.25;

            if(host) {
                // Flip horizontal direction if we run into a wall
                if(Directions.Left == host.direction) {
                    host.direction = Directions.Right;
                } else if(Directions.Right == host.direction) {
                    host.direction = Directions.Left;
                }
            } else {
                ::log("NO HOST!!!");
            }
        }

        base.update(dt);
    }
}
