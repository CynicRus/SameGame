precision highp float;

uniform float time;
uniform vec2 mouse;
uniform vec2 resolution;
uniform sampler2D texture;


mat2 rotate2D(float r) {
    return mat2(cos(r), sin(r), -sin(r), cos(r));
}

void main()
{
    // Normalized pixel coordinates (from 0 to 1)
    vec2 uv = .5*(texture.xy-.5*texture.xy)/texture.y;
    vec3 col = vec3(0);
    float t = time;
    
    vec2 n = vec2(0);
    vec2 q = vec2(0);
    vec2 p = uv*1.5;
    float d = dot(p,p);
    float S = 22.;
    float a = -0.005;
    mat2 m = rotate2D(5.);

    for (float j = 0.; j < 5.; j++) {
        p *= m;
        n *= m;
        q = p * S + t * 4. + sin(t * 1. - d * 8.) * .0018 + 3.*j - .95*n; // wtf???
        a += dot(cos(q)/S, vec2(.2));
        n -= sin(q);
        S *= 1.4;
    }

    col = vec3(1.5, 3., 4.5) * (a + .182) + 9.*a + a + d;
    
    
    // Output to screen
    gl_FragColor = vec4(col,1.0);
}