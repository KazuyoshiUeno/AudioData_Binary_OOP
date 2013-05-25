uniform sampler2DRect src; //テクスチャの変数名をuniform型で宣言
uniform float val; //ぼかす幅
void main( void )
{  
   vec4 sum = vec4(0.0);
   vec2 xy = gl_TexCoord[0].xy;
 
   sum += texture2DRect(src, xy + vec2(0.0, -4.0 * val)) * 0.05;
   sum += texture2DRect(src, xy + vec2(0.0, -3.0 * val)) * 0.09;
   sum += texture2DRect(src, xy + vec2(0.0, -2.0 * val)) * 0.12;
   sum += texture2DRect(src, xy + vec2(0.0, -val)) * 0.15;
   sum += texture2DRect(src, xy + vec2(0.0, 0.0)) * 0.16;
   sum += texture2DRect(src, xy + vec2(0.0, val)) * 0.15;
   sum += texture2DRect(src, xy + vec2(0.0, 2.0 * val)) * 0.12;
   sum += texture2DRect(src, xy + vec2(0.0, 3.0 * val)) * 0.09;
   sum += texture2DRect(src, xy + vec2(0.0, 4.0 * val)) * 0.05;
 
   gl_FragColor = sum;
}