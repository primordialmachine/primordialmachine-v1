@{title = "Ring 1 :: Memory Library"}
@{tableOfContents = "./api/ring1-library/_toc.ihtml"}
@(>"./_header.html.t")

<h2 id="ring1_memory_copyarrayslow">Ring1_Memory_copyArraySlow</h2>
<p>Copy Bytes from a source memory block to a target memory block.</p>
<p><code class="block">
Ring1_Result<br/>
Ring1_Memory_copyArraySlow<br/>
&nbsp;&nbsp;(<br/>
&nbsp;&nbsp;&nbsp;&nbsp;void *p,<br/>
&nbsp;&nbsp;&nbsp;&nbsp;const void *q,<br/>
&nbsp;&nbsp;&nbsp;&nbsp;size_t numberOfElements,<br/>
&nbsp;&nbsp;&nbsp;&nbsp;size_t elementSize<br/>
&nbsp;&nbsp;)
</code></p>

<p>
This function copies
<code class="inline">numberOfElements * elementSize</code>
Bytes from a source memory block pointed to by
<code class="inline">q</code>
to a target memory block pointed to by
<code class="inline">p</code>.
</p>

<p>
This function handles copying between overlapping memory blocks
However, its slower than <a href="@(baseurl)api/ring1-library/memory-library/Ring1_Memory_copyArrayFast">Ring1_Memory_copyArrayFast</a>.
If you can assert that the memory blocks are not overlapping,
use the faster <a href="@(baseurl)api/ring1-library/memory-library/Ring1_Memory_copyArrayFast">Ring1_Memory_copyArrayFast</a>.
</p>

<h3>Parameter variables</h3>
<dl class="parameters">
  <dt><code class="inline">p</code></dt><dd>A pointer to the target memory block.</dd>
  <dt><code class="inline">q</code></dt><dd>A pointer to the source memory block.</dd>
  <dt><code class="inline">numberOfElements, elementSize</code></dt><dd><code class="inline">numberOfElements * elementSize</code> is the number of Bytes to copy.</dd>
</dl>

<h3>Return Values</h3>
<p><code class="inline">Ring1_Result_Success</code> on success, <code class="inline">Ring1_Result_Failure</code> on failure.</p>

<h3>Post Conditions</h3>
<p>If this function fails, then it sets the <a href="@(baseurl)api/ring1-library/status-library">by-thread status variable</a>.
<p>Below is a list of failure conditions and the status codes indicating them.</p>
<dl class="parameters">
  <dt><code class="inline">Ring1_Status_InvalidArgument</code></dt>
  <dd>
  <p>if <code class="inline">p</code> and/or <code class="inline">q</code> is <code class="inline">NULL</code></p>
  </dd>
  <dt><code class="inline">Ring1_Status_NumericOverflow</code></dt>
  <dd>if the value <code class="inline">numberOfElements * elementSize</code> is not representable by <code>size_t</code> values</dd>
</dl>
<p>If this function fails, neither <code class="inline">p</code> nor <code class="inline">p</code> is not dereferenced.</p>

@(>"./_footer.html.t")
