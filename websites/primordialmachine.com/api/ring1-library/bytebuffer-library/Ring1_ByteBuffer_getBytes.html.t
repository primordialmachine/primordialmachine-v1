@{title = "Ring 1 :: Byte Buffer Library"}
@{tableOfContents = "./api/ring1-library/_toc.ihtml"}
@(>"./_header.html.t")

<h2 id="ring1_bytebuffer_getbytes">Ring1_ByteBuffer_getBytes</h2>
<p>Get a pointer to the Bytes of a Byte buffer.</p>
<p><code class="block">
Ring1_Result<br/>
Ring1_ByteBuffer_getBytes<br/>
&nbsp;&nbsp;(<br/>
&nbsp;&nbsp;&nbsp;&nbsp;char const **result,<br/>
&nbsp;&nbsp;&nbsp;&nbsp;Ring1_ByteBuffer *byteBuffer<br/>
&nbsp;&nbsp;)
</code></p>

<p>
This function gets a pointer to the Bytes of a Byte buffer.
</p>

<h3>Parameter variables</h3>
<dl>
  <dt><code class="inline">result</code></dt>
  <dd>A pointer to a <code class="inline">char const *</code> variable.</dd>

  <dt><code class="inline">byteBuffer</code></dt>
  <dd>A pointer to the Byte buffer.</dd>
</dl>

<h3>Return Values</h3>
<p><code class="inline">Ring1_Result_Success</code> on success, <code class="inline">Ring1_Result_Failure</code> on failure.</p>

<h3>Post Conditions</h3>
<p>If this function fails, then it sets the <a href="@(baseurl)api/ring1-library/status-library">by-thread status variable</a>.</p>
<p>Below is a list of failure conditions and the status codes indicating them.</p>
<dl class="parameters">
  <dt><code class="inline">Ring1_Status_InvalidArgument</code></dt>
  <dd><code class="inline">result</code> and/or <code class="inline">byteBuffer</code> is a null pointer</dd>
</dl>

@(>"./_footer.html.t")
