@{title = "Ring 1 :: Memory Library"}
@{tableOfContents = "./api/ring1-library/_toc.ihtml"}
@(>"./_header.html.t")

<h2 id="ring1_memory_zerofillarray">Ring1_Memory_zeroFillArray</h2>
<p>Zero a memory block.</p>
<p><code class="block">
Ring1_Result<br/>
Ring1_Memory_zeroFillArray<br/>
&nbsp;&nbsp;(<br/>
&nbsp;&nbsp;&nbsp;&nbsp;void *p,<br/>
&nbsp;&nbsp;&nbsp;&nbsp;size_t numberOfElements,<br/>
&nbsp;&nbsp;&nbsp;&nbsp;size_t elementSize<br/>
&nbsp;&nbsp;)
</code></p>

<p>
This function assignes the value zero to the first <code class="inline">numberOfElements * elementSize</code> Bytes of the memory block pointed to by
<code class="inline">p</code>. In particular, this function fails if the product of <code>numberOfElements * elementSize</code> would overflow.
</p>

<h3>Parameter variables</h3>
<dl class="parameters">
  <dt><code class="inline">p</code></dt>
  <dd>A pointer to a memory block of <code class="inline">n</code> Bytes.</dd>

  <dt><code class="inline">numberOfElements, elementSize</code></dt>
  <dd>The product <code class="inline">numberOfElements, elementSize</code> the number of Bytes.</dd>
</dl>

<h3>Return Values</h3>
<p><code class="inline">Ring1_Result_Success</code> on success, <code class="inline">Ring1_Result_Failure</code> on failure.</p>

<h3>Post Conditions</h3>
<p>If this function fails, then it sets the <a href="@(baseurl)api/ring1-library/status-library">by-thread status variable</a>.
<p>Below is a list of failure conditions and the status codes indicating them.</p>
<dl class="parameters">
  <dt><code class="inline">Ring1_Status_InvalidArgument</code></dt>
  <dd><code class="inline">p</code> is <code class="inline">NULL</code></dd>

  <dt><code class="inline">Ring1_Status_NumericOverflow</code></dt>
  <dd><code class="inline">numberOfElements * elementSize</code> overflows</dd>
</dl>
<p>If this function fails, <code class="inline">p</code> is not dereferenced.</p>

@(>"./_footer.html.t")
