@{title = "Ring 1 :: Byte Buffer Library"}
@{tableOfContents = "./api/ring1-library/_toc.ihtml"}
@(>"./_header.html.t")

<h2 id="ring1_bytebuffer_uninitialize">Ring1_ByteBuffer_uninitialize</h2>
<p>Uninitialize a Byte buffer.</p>
<p><code class="block">
void<br/>
Mkx_ByteBuffer_uninitialize<br/>
&nbsp;&nbsp;(<br/>
&nbsp;&nbsp;&nbsp;&nbsp;Mkx_ByteBuffer *byteBuffer<br/>
&nbsp;&nbsp;)
</code></p>

<p>
This function uninitializes an initialized <code>Ring1_ByteBuffer</code> object.
If <code class="inline">byteBuffer</code> is a null pointer, this function returns immediatly.
</p>

<h3>Parameter variables</h3>
<dl>
  <dt><code class="inline">byteBuffer</code></dt>
  <dd>A pointer to a <code class="inline">Ring1_ByteBuffer</code> object or a null pointer.</dd>
</dl>

<h3>Post Conditions</h3>
<p>
If <code class="inline">byteBuffer</code> is a null pointer, this function did nothing.
Otherwise the <code class="inline">Ring1_ByteBuffer</code> object was uninitialized.
</p>

@(>"./_footer.html.t")
