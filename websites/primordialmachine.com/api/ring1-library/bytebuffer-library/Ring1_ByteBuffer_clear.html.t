@{title = "Ring 1 :: Byte Buffer Library"}
@{tableOfContents = "./api/ring1-library/_toc.ihtml"}
@(>"./_header.html.t")

<h2 id="ring1_bytebuffer_clear">Ring1_ByteBuffer_clear</h2>
<p>Clear a Byte buffer.</p>
<p><code class="block">
Ring1_Result<br/>
Ring1_ByteBuffer_clear<br/>
&nbsp;&nbsp;(<br/>
&nbsp;&nbsp;&nbsp;&nbsp;Ring1_ByteBuffer *byteBuffer<br/>
&nbsp;&nbsp;)
</code></p>

<p>
This function clears a Byte buffer.
</p>

<h3>Parameter variables</h3>
<dl>
  <dt><code class="inline">byteBuffer</code></dt>
  <dd>A pointer to the Byte buffer.</dd>
</dl>

<h3>Return Values</h3>
<p><code class="inline">Ring1_Result_Success</code> on success, <code class="inline">Ring1_Result_Failure</code> on failure.</p>

<h3>Post Conditions</h3>
<p>If this function fails, then it sets the <a href="@(baseurl)api/ring1-library/status-library">by-thread status variable</a>.</p>
<p>This function fails if and only if <code class="inline">byteBuffer</code> is a null pointer.</p>
<p>If this function succeeds, the Byte was appended to this Byte buffer.</p>

@(>"./_footer.html.t")
