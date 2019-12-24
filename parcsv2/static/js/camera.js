class Camera {
    constructor(lookFrom, lookAt, up, fov, aspect, focusDist) {
        this.up = up.normalized();
        this.origin = lookFrom;
        this.direction = lookAt.subtract(lookFrom).normalized();
        
        let theta = fov * Math.PI / 180;
        let halfHeight = Math.tan(theta / 2);
        let halfWidth = halfHeight * aspect;
        
        this.right = this.up.cross(this.direction).normalized();
        //const corner = this.right.multiply(halfWidth).add(this.up.multiply(halfHeight)).subtract(this.direction.multiply(focusDist));
        this.bottomLeftCorner = this.right.multiply(halfWidth).add(this.up.multiply(halfHeight)).subtract(this.direction.multiply(focusDist));
        this.horizontal = this.right.multiply(2 * halfWidth);
        this.vertical = this.up.multiply(2 * halfHeight);
    }
    
    getRay(u,v) {
        return new Ray(this.origin, this.horizontal.multiply(u).add(this.vertical.multiply(v)).subtract(this.bottomLeftCorner))
    }
}