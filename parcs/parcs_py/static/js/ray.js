class Ray {
    constructor(origin, direction) {
        this.origin = origin;
        this.direction = direction;
        this.direction.normalize();
    }
    
    
}