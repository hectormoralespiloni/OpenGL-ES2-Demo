precision lowp float;

uniform sampler2D myTexture;

varying vec4 v_color;
varying vec2 v_texCoords;

void main()
{
    gl_FragColor = v_color * texture2D(myTexture, v_texCoords);
}