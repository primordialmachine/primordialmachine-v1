@{title = "Ring 1 :: Memory Library"}
@{tableOfContents = "./api/ring1-library/_toc.ihtml"}
@(>"./_header.html.t")

<h2 id="ring1_memory_deallocate">Ring1_Memory_deallocate</h2>
<p>Deallocate a memory block.</p>
<p><code class="block">
Ring1_Result<br/>
Ring1_Memory_deallocate<br/>
&nbsp;&nbsp;(<br/>
&nbsp;&nbsp;&nbsp;&nbsp;void *p<br/>
&nbsp;&nbsp;)
</code></p>

<p>
This function deallocates a memory block previously allocated by a call to <code class="inline">Ring1_Memory_allocate</code> or
<code class="inline">Ring1_Memory_allocateArray</code>.
The function silently ignores null pointers.
</p>

<h3>Parameter variables</h3>
<dl class="parameters">
  <dt><code class="inline">p</code></dt>
  <dd>
  A pointer to a memory block previously allocate by a call to <code class="inline">Ring1_Memory_allocate</code> or <code class="inline">Ring1_Memory_allocateArray</code>.
  </dd>
</dl>

<h3>Return Values</h3>
<p><code class="inline">Ring1_Result_Success</code> on success, <code class="inline">Ring1_Result_Failure</code> on failure.</p>
<p>This function always succeeds.</p>

@(>"./_footer.html.t")
