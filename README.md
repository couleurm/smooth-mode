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
