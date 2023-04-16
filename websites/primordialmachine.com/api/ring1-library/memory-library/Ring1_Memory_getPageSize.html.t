@{title = "Ring 1 :: Memory Library"}
@{tableOfContents = "./api/ring1-library/_toc.ihtml"}
@(>"./_header.html.t")

<h2 id="ring1_memory_getpagesize">Ring1_Memory_getPageSize</h2>
<p>Get the page size.</p>
<p><code class="block">
Ring1_Result<br/>
Ring1_Memory_getPageSize<br/>
&nbsp;&nbsp;(<br/>
&nbsp;&nbsp;&nbsp;&nbsp;size_t **result<br/>
&nbsp;&nbsp;)
</code></p>

<p>
This function gets the page size.
</p>

<h3>Parameter variables</h3>
<dl class="parameters">
  <dt><code class="inline">result</code></dt>
  <dd>A pointer to a <code class="inline">size_t *</code> variable.</dd>
</dl>

<h3>Return Values</h3>
<p><code class="inline">Ring1_Result_Success</code> on success, <code class="inline">Ring1_Result_Failure</code> on failure.</p>

<h3>Post Conditions</h3>
<p>If this function fails, then it sets the <a href="@(baseurl)api/ring1-library/status-library">by-thread status variable</a>.
<p>Below is a list of failure conditions and the status codes indicating them.</p>
<dl class="parameters">
  <dt><code class="inline">Ring1_Status_InvalidArgument</code></dt>
  <dd><code class="inline">result</code> is <code class="inline">NULL</code></dd>
</dl>
<p>If this function fails, <code class="inline">result</code> is not dereferenced.</p>

<p>If this function succeeds, <code class="inline">*result</code> is assigned the pages size.</p>

@(>"./_footer.html.t")
