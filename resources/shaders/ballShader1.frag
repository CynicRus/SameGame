precision highp float;

uniform float time;
uniform vec2 size;
uniform sampler2D texture;


mat2 rotate2D(float r) {
    return mat2(cos(r), sin(r), -sin(r), cos(r));
}


void main()
{
	vec4  tex = texture2D( texture, gl_TexCoord[0].xy );
    vec2 uv = (tex.xy-.5*size)/size.x/12;

    vec3 col = vec3(0);
    float t = time;
    
    vec2 n = vec2(0);
    vec2 q = vec2(0);
    vec2 p = uv;
    float d = dot(p,p);
    float S = 22.;
    float a = 0.0;
    mat2 m = rotate2D(5.);

    for (float j = 0.; j < 8.; j++) {
        p *= m;
        n *= m;
        q = p * S + t * 4. + sin(t * 1. - d * 8.) * .0018 + 3.*j - .95*n; 
        a += dot(cos(q)/S, vec2(.2));
        n -= sin(q);
        S *= 1.4;
    }

    col = (tex.rgb * 4.5) * (a + .2) + a + a - d;	  
    gl_FragColor = vec4(tex.rgb + col * tex.a,tex.a);
}