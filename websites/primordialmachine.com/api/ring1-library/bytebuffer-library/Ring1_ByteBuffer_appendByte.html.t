@{title = "Ring 1 :: Byte Buffer Library"}
@{tableOfContents = "./api/ring1-library/_toc.ihtml"}
@(>"./_header.html.t")

<h2 id="ring1_bytebuffer_appendbyte">Ring1_ByteBuffer_appendByte</h2>
<p>Append a Bytes to a Byte buffer.</p>
<p><code class="block">
int<br/>
Mkx_ByteBuffer_appendByte<br/>
&nbsp;&nbsp;(<br/>
&nbsp;&nbsp;&nbsp;&nbsp;Mkx_ByteBuffer *byteBuffer,<br/>
&nbsp;&nbsp;&nbsp;&nbsp;const char byte<br/>
&nbsp;&nbsp;)
</code></p>

<p>
This function appends a Byte <code class="inline">byte</code> to a Byte Buffer.
It returns <code class="inline">0</code> on success and a non-zero value on failure.
</p>

<h3>Parameter variables</h3>
<dl>
  <dt><code class="inline">byteBuffer</code></dt><dd>A pointer to the Byte buffer.</dd>
  <dt><code class="inline">byte</code></dt><dd>The Byte.</dd>
</dl>

<h3>Return Values</h3>
<p>
<code class="inline"><a href="@(baseurl)api/ring1-library/result-library/result-codes">Ring1_Result_Success</a></code> on success,
<code class="inline"><a href="@(baseurl)api/ring1-library/result-library/result-codes">Ring1_Result_Failure</a></code> on failure.
</p>

<h3>Post Conditions</h3>
<p>
If this function fails, then it sets the <a href="@(baseurl)api/ring1-library/status-library">by-thread status variable</a>.
</p>
<p>Below is a list of failure conditions and the status codes indicating them.</p>
<dl class="parameters">
  <dt><code class="inline">Ring1_Status_InvalidArgument</code></dt>
  <dd><code class="inline">byteBuffer</code> is a null pointer</dd>
  
  <dt><code class="inline">Ring1_Status_AllocationFailed</code></dt>
  <dd>an allocation failed</dd>
</dl>

<p>
If this function succeeds, the Byte was appended to this Byte buffer.
</p>

@(>"./_footer.html.t")
