@{title = "Ring 1 :: Memory Library"}
@{tableOfContents = "./api/ring1-library/_toc.ihtml"}
@(>"./_header.html.t")

<h2 id="ring1_memory_compare">Ring1_Memory_compare</h2>
<p>Compare memory blocks.</p>
<p><code class="block">
Ring1_Result<br/>
Ring1_Memory_compare<br/>
&nbsp;&nbsp;(<br/>
&nbsp;&nbsp;&nbsp;&nbsp;const void *p,<br/>
&nbsp;&nbsp;&nbsp;&nbsp;size_t n,<br/>
&nbsp;&nbsp;&nbsp;&nbsp;const void *q,<br/>
&nbsp;&nbsp;&nbsp;&nbsp;size_t m,<br/>
&nbsp;&nbsp;&nbsp;&nbsp;int flags<br/>
&nbsp;&nbsp;)
</code></p>

<p>This function compares two memory blocks either lexicographically or colexicographically.</p>

<h3>Parameter variables</h3>
<dl class="parameters">
  <dt><code class="inline">p</code></dt><dd>A pointer to a memory block of <code class="inline">n</code> Bytes.</dd>
  <dt><code class="inline">n</code></dt><dd>The size, in Bytes, of the memory block pointed to by <code class="inline">p</code>.</dd>
  <dt><code class="inline">q</code></dt><dd>A pointer to a memory block of <code class="inline">m</code> Bytes.</dd>
  <dt><code class="inline">m</code></dt><dd>The size, in Bytes, of the memory block pointed to by <code class="inline">q</code>.</dd>
  <dt><code class="inline">flags</code></dt><dd>`flags` Must be one of <code class="inline">MKX_MEMORY_COMPARE_LEXICOGRAPHIC</code> or
  <code class="inline">MKX_MEMORY_COMPARE_COLEXICOGRAPHIC</code>. If <code class="inline">MKX_MEMORY_COMPARE_LEXICOGRAPHIC</code> is passed,
  the memory blocks are compared lexicographically. If <code class="inline">MKX_MEMORY_COMPARE_COLEXICOGRAPHIC</code> is passed, the
  memory blocks are compared colexicographically.</dd>
</dl>

<h3>Return value</h3>
<ul>
  <li>A negative value if the memory block pointed to by <code class="inline">p</code> is (co)lexicographically smaller than the memory block pointed to by <code class="inline">q</code>.</li>
  <li>A positive value if the memory block pointed to by <code class="inline">p</code> is (co)lexicographically greater than the memory block pointed to by <code class="inline">q</code>.</li>
  <li>Zero if both memory blocks are (co)lexicographically equal.</li>
</ul>

<h3>Return Values</h3>
<p><code class="inline">Ring1_Result_Success</code> on success, <code class="inline">Ring1_Result_Failure</code> on failure.</p>

@(>"./_footer.html.t")
