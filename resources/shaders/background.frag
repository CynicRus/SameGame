#ifdef GL_ES
precision mediump float;
#endif

uniform float time;
uniform vec2 resolution;

float snow(vec2 uv,float scale)
{
	float w=smoothstep(1.,0.,-uv.y*(scale/10.));if(w<.1)return 0.;
	uv+=time/scale;uv.y+=time*0.1/scale;uv.x+=sin(uv.y+time*.5)/scale;
	uv*=scale;vec2 s=floor(uv),f=fract(uv),p;float k=3.,d;
	p=.5+.35*sin(111.*fract(sin((s+p+scale)*mat2(7,3,6,5))*5.))-f;d=length(p);k=min(d,k);
	k=smoothstep(0.,k,sin(f.x+f.y)*0.004);
    	return k*w;
}

void main(void){
	vec2 uv=(gl_FragCoord.xy*2.-resolution.xy)/resolution.y; 
	vec3 finalColor=vec3(0);
	float c=smoothstep(1.,0.11,clamp(uv.y*.3+.8,0.,.75));
	//c+=snow(uv,30.)*.0;
        //c+=snow(uv,20.)*.0;
	//c+=snow(uv,15.)*.0;
	//c+=snow(uv,10.);
	c+=snow(uv,7.);
	//c+=snow(uv,6.);
	//c+=snow(uv,5.);
	finalColor=(vec3(c));
	finalColor *= vec3(0.2, 0.5, 0.9);
	gl_FragColor = vec4(finalColor,1);
}