#version 110

uniform sampler2DRect background_sampler;
uniform sampler2DRect shadow_sampler;
uniform sampler2DRect radius_sampler;

uniform bool flip_shadow;
uniform vec2 sampler_size;

varying vec2 texcoord0;

void main()
{
    vec2 FragTexCoord = vec2(texcoord0.x, sampler_size.y - texcoord0.y);
    vec2 ShadowCoord;

    if(flip_shadow) {
        ShadowCoord = vec2(sampler_size.x - texcoord0.x, sampler_size.y - texcoord0.y);
    } else {
        ShadowCoord = vec2(texcoord0.x, sampler_size.y - texcoord0.y);
    }
    
    vec4 tex = texture2DRect(background_sampler, FragTexCoord);
    vec4 texCorner = texture2DRect(radius_sampler, texcoord0);

    vec4 texDiff = texture2DRect(shadow_sampler, ShadowCoord);

    tex.rgb = tex.rgb - texDiff.rgb*tex.rgb;

    tex.a = texCorner.a;

    gl_FragColor = tex;
}
