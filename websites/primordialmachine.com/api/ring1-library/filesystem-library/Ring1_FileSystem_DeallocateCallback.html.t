@{title = "Ring 1 :: File System Library"}
@{tableOfContents = "./api/ring1-library/_toc.ihtml"}
@(>"./_header.html.t")

<h2 id="ring1_filesystem_deallocatecallback">Ring1_FileSystem_DeallocateCallback</h2>
<p>Type of a function deallocating a memory block.</p>
<p><code class="block">
Ring1_Result<br/>
(Ring1_FileSystem_DeallocateCallback)<br/>
&nbsp;&nbsp;(<br/>
&nbsp;&nbsp;&nbsp;&nbsp;void *p<br/>
&nbsp;&nbsp;)
</code></p>

<p>
A function of this type deallocates a memory block previously allocated by a call to the  corresponding
<code class="inline">Ring1_FileSystem_AllocateCallback</code>. A function of this type silently ignores
null pointers.
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
