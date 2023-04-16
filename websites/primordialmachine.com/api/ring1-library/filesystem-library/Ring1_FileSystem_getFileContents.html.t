@{title = "Ring 1 :: Memory Library"}
@{tableOfContents = "./api/ring1-library/_toc.ihtml"}
@(>"./_header.html.t")

<h2 id="ring1_filesystem_getfilecontents">Ring1_FileSystem_getFileContents</h2>
<p>Gets the contents of a file.</p>
<p><code class="block">
Ring1_Result<br/>
Ring1_FileSystem_getFileContents<br/>
&nbsp;&nbsp;(<br/>
&nbsp;&nbsp;&nbsp;&nbsp;char const *pathname,<br/>
&nbsp;&nbsp;&nbsp;&nbsp;Ring1_FileSystem_Allocate *allocate,<br/>
&nbsp;&nbsp;&nbsp;&nbsp;Ring1_FileSystem_Deallocate *deallocate,<br/>
&nbsp;&nbsp;&nbsp;&nbsp;void **bytes<br/>
&nbsp;&nbsp;&nbsp;&nbsp;size_t *numberOfBytes<br/>
&nbsp;&nbsp;)
</code></p>

<p>
This function gets the contents of a file.
</p>

<h3>Parameter variables</h3>
<dl>
  <dt><code class="inline">pathname</code></dt>
  <dd>The pathname of the file.</dd>

  <dt><code class="inline">allocate</code></dt>
  <dd>A pointer to a <code class="inline">Ring1_FileSystem_Allocate</code> function.</dd>
  <dt><code class="inline">deallocate</code></dt>
  <dd>A pointer to a <code class="inline">Ring1_FileSystem_Deallocate</code> function.</dd>

  <dt><code class="inline">bytes</code></dt>
  <dd>A pointer to a <code class=inline">void *</code> variable.</dd>
  <dt><code class="inline">numberOfBytes</code></dt>
  <dd>A pointer to a <code class=inline">size_t</code> variable.</dd>
</dl>

<h3>Return Values</h3>
<p><code class="inline">Ring1_Result_Success</code> on success, <code class="inline">Ring1_Result_Failure</code> on failure.</p>

<h3>Post Conditions</h3>
<p>If this function fails, then it sets the <a href="@(baseurl)api/ring1-library/status-library">by-thread status variable</a>.
<p>Below is a list of failure conditions and the status codes indicating them.</p>
<dl class="parameters">
  <dt><code class="inline">Ring1_Status_InvalidArgument</code></dt>
  <dd>
    <code class="inline">pathname</code>,
    <code class="inline">allocate</code>,
    <code class="inline">deallocate</code>,
    <code class="inline">bytes</code>, and/or
    <code class="inline">numberOfBytes</code>,  
    is
    <code class="inline">NULL</code>.
  </dd>
  
  <dt><code class="inline">Ring1_Status_AllocationFailed</code></dt>
  <dd>An allocation failed.</dd>
  
  <dt><code class="inline">Ring1_Status_EnvironmentFailed</code></dt> 
  <dd>File does not exist.</dd>
  
  <dt><code class="inline">Ring1_Status_EnvironmentFailed</code></dt> 
  <dd>File exists but is not of the right category.</dd>
  
  <dt><code class="inline">Ring1_Status_EnvironmentFailed</code></dt> 
  <dd>Getting the file's contents failed.</dd>

</dl>
<p>If this function fails, neither <code class="inline">bytes</code> nor <code class="inline">numberOfBytes</code> are dereferenced.</p>

<p>
If this function succeeds, <code class="inline">*numberOfBytes</code> is assigned the number of Bytes of the contents of the file and
<code class="inline">*bytes</code> is assigned an array with the Byte values of the contents of the file.
</p>


@(>"./_footer.html.t")
