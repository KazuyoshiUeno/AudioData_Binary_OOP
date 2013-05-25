uniform sampler2DRect tex1; //テクスチャの変数名をuniform型で宣言
//uniform float num;
void main( void )
{  
	  vec2 xy = gl_TexCoord[0].xy;//テクスチャ座標を取得 0 ~ 1.0  
    vec4 color = texture2DRect(tex1, xy);//テクスチャからstの座標でvec4型の色情報を取得
    gl_FragColor = vec4(vec3(1) - color.rgb,1); //最終出力の色を設定
}