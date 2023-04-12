@{title = "Ring 1 :: Byte Buffer Library"}
@{tableOfContents = "./api/ring1-library/_toc.ihtml"}
@(>"./_header.html.t")

<h2 id="ring1_bytebuffer">Ring1_ByteBuffer</h2>
<p>The type of a Byte buffer.</p>
<p><code class="block">
typedef struct Ring1_ByteBuffer { ... } Ring1_ByteBuffer;<br/>
</code></p>

<p>
A buffer of Bytes. The size is automatically adjusted as Bytes are added and removed.

The "appendByte" and "accessByte" operations are constant time in all cases,
the "insertByte" and the "insertBytes" operations linear time in worst case.
The "appendBytes" operations are linear in the number of Bytes in worst case.


An <code class="inline">Mkx_ByteBuffer</code> can be allocated on the stack or on the heap and can be part of struct types.
Before using the Byte bffer object, it must be initialized using <code class="inline">Mkx_ByteBuffer_initialize</code>.
When no longer required, it must be uninitialized using <code class="inline ">Mkx_ByteBuffer_uninitialize</code>.
</p>

@(>"./_footer.html.t")
