@{title = "Ring 1 :: Memory Library"}
@{tableOfContents = "./api/ring1-library/_toc.ihtml"}
@(>"./_header.html.t")

<h2 id="ring1_memory_copyslow">Ring1_Memory_copySlow</h2>
<p>Copy Bytes from a source memory block to a target memory block.</p>
<p><code class="block">
Ring1_Result<br/>
Ring1_Memory_copySlow<br/>
&nbsp;&nbsp;(<br/>
&nbsp;&nbsp;&nbsp;&nbsp;void *p,<br/>
&nbsp;&nbsp;&nbsp;&nbsp;const void *q,<br/>
&nbsp;&nbsp;&nbsp;&nbsp;size_t n<br/>
&nbsp;&nbsp;)
</code></p>

<p>
This function copies
<code class="inline">n</code>
Bytes from a source memory block pointed to by
<code class="inline">q</code>
to a target memory block pointed to by
<code class="inline">p</code>.
</p>

<p>
This function handles copying between overlapping memory blocks
However, its slower than <a href="@(baseurl)api/ring1-library/memory-library/Ring1_Memory_copyFast">Ring1_Memory_copyFast</a>.
If you can assert that the memory blocks are not overlapping,
use the faster <a href="@(baseurl)api/ring1-library/memory-library/Ring1_Memory_copyFast">Ring1_Memory_copyFast</a>.
</p>

<h3>Parameter variables</h3>
<dl class="parameters">
  <dt><code class="inline">p</code></dt><dd>A pointer to the target memory block.</dd>
  <dt><code class="inline">q</code></dt><dd>A pointer to the source memory block.</dd>
  <dt><code class="inline">n</code></dt><dd>The number of Bytes to copy.</dd>
</dl>

<h3>Return value</h3>
<p>This function returns <code class="inline">0</code> on success, a non-zero value on failure.</p>

<h3>Post Conditions</h3>
<p>If this function fails, then it sets the <a href="@(baseurl)api/ring1-library/status-library">by-thread status variable</a>.
<p>Below is a list of failure conditions and the status codes indicating them.</p>
<dl class="parameters">
  <dt><code class="inline">Ring1_Status_InvalidArgument</code></dt>
  <dd>
  <p>if <code class="inline">p</code> and/or <code class="inline">q</code> is <code class="inline">NULL</code></p>
  </dd>
</dl>
<p>If this function fails, neither <code class="inline">p</code> nor <code class="inline">p</code> is not dereferenced.</p>

@(>"./_footer.html.t")
