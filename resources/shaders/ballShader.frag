uniform sampler2D texture;

vec3 hsv(float h, float s, float v){
    vec4 t = vec4(1.0, 2.0 / 3.0, 1.0 / 3.0, 3.0);
    vec3 p = abs(fract(vec3(h) + t.xyz) * 6.0 - vec3(t.w));
    return v * mix(vec3(t.x), clamp(p - vec3(t.x), 0.0, 1.0), s);
}
 
void main(void)
{
   float offs = 1.0 / 48.0; // разрешение текстуры 256*256
   float tex00 = texture2D( texture, gl_TexCoord[0].xy + vec2(-offs,-offs ) ).a;
   float tex10 = texture2D( texture, gl_TexCoord[0].xy + vec2(-offs,  0.0 ) ).a;
   float tex20 = texture2D( texture, gl_TexCoord[0].xy + vec2(-offs, offs ) ).a;
   
   float tex01 = texture2D( texture, gl_TexCoord[0].xy + vec2(  0.0,-offs ) ).a;
   vec4  tex = texture2D( texture, gl_TexCoord[0].xy );
   float tex21 = texture2D( texture, gl_TexCoord[0].xy + vec2(  0.0, offs ) ).a;
   
   float tex02 = texture2D( texture, gl_TexCoord[0].xy + vec2( offs,-offs ) ).a;
   float tex12 = texture2D( texture, gl_TexCoord[0].xy + vec2( offs,  0.0 ) ).a;
   float tex22 = texture2D( texture, gl_TexCoord[0].xy + vec2( offs, offs ) ).a;
   
   float alpha0 = max( max( tex00, tex10 ), tex20 );
   float alpha1 = max( max( tex01, tex.a ), tex21 );
   float alpha2 = max( max( tex02, tex12 ), tex22 );
   
   float alpha = max( max( alpha0, alpha1 ), alpha2 ); 
   
   if( alpha > 0.3 ){alpha = 1.0;}else{alpha = 0.0;}
   float a = tex.a;
   if( tex.a > 0.3 ){a = 1.0;}else{a = 0.0;}
   
   
   vec3 color = hsv(0.5,0.5,0.5);
   vec4 frag_color = vec4( tex.rgb + color, a );
   
   gl_FragColor = frag_color;
}