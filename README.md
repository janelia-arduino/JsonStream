#JsonStream

Authors:

    Peter Polidoro <polidorop@janelia.hhmi.org>

License:

    BSD


JSON encoder/decoder that processes streams sequentially to reduce
buffer memory requirements.

[Usage Examples](./examples)

##Encoder

Writes JSON sequentially to a stream. This avoids having to fill an
encoding buffer before writing to the stream, allowing you to write
JSON of almost any length without exceeding the memory capacity of
small microprocessors.

It is possible to write invalid JSON in this way, however, so some
care needs to be taken that items are added in a meaningful order.

