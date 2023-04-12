@{title = "Ring 1 :: Byte Buffer Library"}
@{tableOfContents = "./api/ring1-library/_toc.ihtml"}
@(>"./_header.html.t")

<h2 id="ring1_bytebuffer_appendbytes">Ring1_ByteBuffer_appendBytes</h2>
<p>Append Bytes to a Byte buffer.</p>
<p><code class="block">
Ring1_Result<br/>
Ring1_ByteBuffer_appendBytes<br/>
&nbsp;&nbsp;(<br/>
&nbsp;&nbsp;&nbsp;&nbsp;Ring1_ByteBuffer *byteBuffer,<br/>
&nbsp;&nbsp;&nbsp;&nbsp;const char *bytes,<br/>
&nbsp;&nbsp;&nbsp;&nbsp;size_t numberOfBytes<br/>
&nbsp;&nbsp;)
</code></p>

<p>
This function appends Bytes to a Byte Buffer.
It expects a pointer <code class="inline">bytes</code> of <code class="inline">numberOfBytes</code> Bytes
and appends these Bytes to the Byte buffer. It returns <code class="inline">0</code> on success and a
non-zero value on failure.
</p>

<h3>Parameter variables</h43
<dl>
  <dt><code class="inline">byteBuffer</code></dt>
  <dd>A pointer to the Byte buffer.</dd>
  
  <dt><code class="inline">bytes</code></dt>
  <dd>A pointer to an array of a <code class="inline">numberOfBytes</code> Bytes.</dd>
  
  <dt><code class="inline">numberOfBytes</code></dt>
  <dd>The number of Bytes in the array pointed to by <code class="inline">bytes</code>.</dd>
</dl>

<h3>Return Values</h3>
<p><code class="inline">Ring1_Result_Success</code> on success, <code class="inline">Ring1_Result_Failure</code> on failure.</p>

<h3>Post Conditions</h3>
<p>
If this function fails, then it sets the <a href="@(baseurl)api/ring1-library/status-library">by-thread status variable</a>.
</p>
<p>Below is a list of failure conditions and the status codes indicating them.</p>
<dl class="parameters">
  <dt><code class="inline">Ring1_Status_InvalidArgument</code></dt>
  <dd><code class="inline">byteBuffer</code> and/or <code class="inline">bytes</code> is a null pointer</dd>
  
  <dt><code class="inline">Ring1_Status_AllocationFailed</code></dt>
  <dd>an allocation failed</dd>
</dl>

<p>
If this function succeeds, the Bytes were appended to this Byte buffer.
</p>

@(>"./_footer.html.t")
