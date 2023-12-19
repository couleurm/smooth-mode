### ⚠ This is just a concept draft, nothing real yet

# OBS Smooth Mode

Frame blending shader plugin for OBS Studio

This is a long awaited alternative to the painstakingly slow and inconvenient use
of Premiere's ``Frame Blending`` and VEGAS's ``Smart resampling`` effects in video editing programs.

### `~` Design:

When configurated for a ``60`` FPS output video:

1. accumulate all frames captured from source in the last ``1/60`` second
2. average (blend) each buffered frames into one
3. pass that single frame to the encoder

### ``+`` Pros:
* If the blending is done before the encoding that means it significantly reduces the encoder load, allowing games to run at an even higher FPS, and allows for more slower/efficient encoding configuration (or Streaming lol)

* editing high fps footage is slow to decode (preview lag) and means you need to do the frame blending each time you export, with it it’d be like editing conventional 30/60 fps videos

### ``-`` Cons:

* the way the blending is configured is final (if it’s 30fps there won’t be any raw footage to blend it back some way differently) 

* for people who like to apply a slow-mo effect in post they’ll either need to cope with choppy slowmos or resort to imperfect solutions like frame interpolation
   * 120FPS __can__ look good, but only REALLY good if there's more weights than the input to output FPS ratio (like 3 times), allowing it to be capped to 30 / 60 fps while still looking okay

# Resources

Here's an agregation of open-source frame blending implementations

# CPU-accelerated (Software)

These solutions are slower but simpler

## temporal mix

ffmpeg filter, example useage:

```
ffmpeg -i input.mp4 -c:v libx264 -vf tmix=frames=4 output.mp4
```

* Docs: https://ffmpeg.org/ffmpeg-filters.html#tmix
* Code: https://git.ffmpeg.org/gitweb/ffmpeg.git/blob/HEAD:/libavfilter/vf_mix.c

## video-blender

by luminance, chad did it in assembly

* Code: https://github.com/unknownopponent/Video-Blender/tree/master/src/blendlib

## vs-frameblender

* https://github.com/couleurm/vs-frameblender

For [smoothie-rs](https://github.com/couleur-tweak-tips/smoothie-rs) I now use [faster code](https://github.com/couleur-tweak-tips/smoothie-rs/blob/405f026b7f66cd74353730e7d00899e181b19ce0/target/scripts/blending.py#L16) (which I honestly admit don't understand much) which makes use of [vs-akarin](https://github.com/AkarinVS/vapoursynth-plugin)

## flowfps

very primitive as it decodes individual image files rgb

code: https://github.com/martinjungblut/flowfps

# GPU-accelerated solutions (Shader)

## OBS shader plugins

* https://github.com/exeldro/obs-shaderfilter
* https://github.com/Xaymar/obs-StreamFX/wiki/OBS-Shading-Language
* https://github.com/Xaymar/obs-StreamFX/wiki/Source-Filter-Transition-Shader

## bxt-rs

replay system addon for half-life, uses vulkan and shaders

* Article: https://bxt.rs/blog/motion-blur-for-half-life-video-recording-with-vulkan/#how-motion-blur-works

* Code: https://github.com/YaLTeR/bxt-rs

## Frameblend.fx

This has an interesting quirk: it dynamically blends whatever FPS your game's getting in the last 1/60th of a second (for 60FPS).

[ReShade](https://reshade.me) lets you overlay shaders on games

* Forum post (the shader's contained in the spoiler): https://reshade.me/forum/shader-presentation/4335-experimental-high-framerate-frame-blending


## recording-mod

experimental minecraft demo system

it has a "Blend Factor" option

https://github.com/ayoeo/recording_mod/tree/master/src/main/resources/assets/minecraft/shaders/program

## danser!

osu demo system

https://github.com/Wieku/danser-go/blob/master/assets/shaders/blend.fsh