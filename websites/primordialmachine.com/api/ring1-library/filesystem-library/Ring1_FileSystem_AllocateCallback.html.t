@{title = "Ring 1 :: File System Library"}
@{tableOfContents = "./api/ring1-library/_toc.ihtml"}
@(>"./_header.html.t")

<h2 id="ring1_filesystem_allocatecallback">Ring1_FileSystem_AllocateCallback</h2>
<p>Allocate a memory block.</p>
<p><code class="block">
Ring1_Result<br/>
Ring1_Memory_allocate<br/>
&nbsp;&nbsp;(<br/>
&nbsp;&nbsp;&nbsp;&nbsp;void **result,<br/>
&nbsp;&nbsp;&nbsp;&nbsp;size_t n<br/>
&nbsp;&nbsp;)+

</code></p>

<p>
A function of this type allocates a memory block of <code class="inline">n</code> Bytes.
</p>

<h3>Parameter variables</h3>
<dl>
  <dt><code class="inline">result</code></dt>
  <dd>A pointer to a <code class="inline">void *</code> variable.</dd>

  <dt><code class="inline">n</code></dt>
  <dd>The size, in Bytes, of the memory block to allocate. Can be zero.</dd>
</dl>

<h3>Return Values</h3>
<p><code class="inline">Ring1_Result_Success</code> on success, <code class="inline">Ring1_Result_Failure</code> on failure.</p>

<h3>Post Conditions</h3>
<p>If this function fails, then it sets the <a href="@(baseurl)api/ring1-library/status-library">by-thread status variable</a>.
<p>Below is a list of failure conditions and the status codes indicating them.</p>
<dl class="parameters">
  <dt><code class="inline">Ring1_Status_InvalidArgument</code></dt>
  <dd><code class="inline">result</code> is <code class="inline">NULL</code></dd>
  <dt><code class="inline">Ring1_Status_AllocationFailed</code></dt>
  <dd>the allocation failed</dd>
</dl>
<p>If this function fails, <code class="inline">result</code> is not dereferenced.</p>

<p>If this function succeeds, <code class="inline">*result</code> is assigned a pointer to a memory block of
   <code class="inline">n</code> Bytes.</p>

@(>"./_footer.html.t")
