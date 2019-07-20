#ifdef GL_ES
precision mediump float;
#endif
varying vec2 V_Texcoord;
uniform sampler2D U_Texture;
void main()
{
	vec4 color=vec4(0.0);
	int coreSize=3;
	float texelOffset=1.0/200.0;
	float kernel[9];
	kernel[6]=1.0;kernel[7]=2.0;kernel[8]=1.0;
	kernel[3]=2.0;kernel[4]=4.0;kernel[5]=2.0;
	kernel[0]=1.0;kernel[1]=2.0;kernel[2]=1.0;
	int index=0;
	for(int y=0;y<coreSize;y++)
	{
		for(int x=0;x<coreSize;x++)
		{
			vec4 currentColor=texture2D(U_Texture,V_Texcoord+vec2(float(-1+x)*texelOffset,float(-1+y)*texelOffset));
			color+=currentColor*kernel[index++];
		}
	}
	color/=16.0;
	gl_FragColor=color;
}
