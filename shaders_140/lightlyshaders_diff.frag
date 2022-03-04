#version 140

uniform sampler2DRect shadow_sampler;
uniform sampler2DRect background_sampler;

uniform int corner_number;
uniform vec2 sampler_size;

in vec2 texcoord0;
out vec4 fragColor;

void main(void)
{
    vec2 ShadowHorCoord;
    vec2 ShadowVerCoord;
    vec2 Shadow0;

    if (corner_number == 0) {
        ShadowHorCoord = vec2(texcoord0.x, sampler_size.y);
        ShadowVerCoord = vec2(0.0, sampler_size.y - texcoord0.y);
        Shadow0 = vec2(0.0, sampler_size.y);
    } else if (corner_number == 1) {
        ShadowHorCoord = vec2(texcoord0.x, sampler_size.y);
        ShadowVerCoord = vec2(sampler_size.x, sampler_size.y - texcoord0.y);
        Shadow0 = vec2(sampler_size.x, sampler_size.y);
    } else if (corner_number == 2) {
        ShadowHorCoord = vec2(texcoord0.x, 0.0);
        ShadowVerCoord = vec2(sampler_size.x, sampler_size.y - texcoord0.y);
        Shadow0 = vec2(sampler_size.x, 0.0);
    } else if (corner_number == 3) {
        ShadowHorCoord = vec2(texcoord0.x, 0.0);
        ShadowVerCoord = vec2(0.0, sampler_size.y - texcoord0.y);
        Shadow0 = vec2(0.0, 0.0);
    }

    vec2 FragTexCoord = vec2(texcoord0.x, sampler_size.y - texcoord0.y);

    vec4 tex = texture(background_sampler, FragTexCoord);

    vec4 tex0 = texture(background_sampler, Shadow0);
    vec4 texShadow0 = texture(shadow_sampler, Shadow0);

    vec4 texHorCur = texture(background_sampler, ShadowHorCoord);
    vec4 texVerCur = texture(background_sampler, ShadowVerCoord);
    vec4 texShadowHorCur = texture(shadow_sampler, ShadowHorCoord);
    vec4 texShadowVerCur = texture(shadow_sampler, ShadowVerCoord);

    vec3 diffHorCur = (texHorCur.rgb-texShadowHorCur.rgb)*(tex.rgb/texHorCur.rgb);
    vec3 diffVerCur = (texVerCur.rgb-texShadowVerCur.rgb)*(tex.rgb/texVerCur.rgb);

    vec3 diff0 = (tex0.rgb - texShadow0.rgb)*(tex.rgb/tex0.rgb);

    vec3 diff = diffHorCur + (diffVerCur-diff0);

    fragColor = vec4(diff.rgb/tex.rgb, 1.0);
}
