@{title = "Ring 1 :: Byte Buffer Library"}
@{tableOfContents = "./api/ring1-library/_toc.ihtml"}
@(>"./_header.html.t")

<h2 id="ring1_bytebuffer_initialize">Ring1_ByteBuffer_initialize</h2>
<p>Initialize a Byte buffer.</p>
<p><code class="block">
Ring1_Result<br/>
Ring1_ByteBuffer_initialize<br/>
&nbsp;&nbsp;(<br/>
&nbsp;&nbsp;&nbsp;&nbsp;Ring1_ByteBuffer *byteBuffer<br/>
&nbsp;&nbsp;)
</code></p>

<p>
This function initializes an uninitialized <code class="inline">Ring1_ByteBuffer</code> object.
</p>

<h3>Parameter variables</h3>
<dl>
  <dt><code class="inline">byteBuffer</code></dt>
  <dd>A pointer to an uninitialized <code class="inline">Ring1_ByteBuffer</code> object.</dd>
</dl>

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

<p>If this function fails, <code class="inline">byteBuffer</code> is not dereferenced.</p>

<p>If this function succeeds, the <code class="inline">Ring1_ByteBuffer</code> object is initialized.</p>

<h3>Return Values</h3>
<p><code class="inline">Ring1_Result_Success</code> on success, <code class="inline">Ring1_Result_Failure</code> on failure.</p>

@(>"./_footer.html.t")
