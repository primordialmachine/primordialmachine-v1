@{title = "Ring 1 :: File System Library"}
@{tableOfContents = "./api/ring1-library/_toc.ihtml"}
@(>"./_header.html.t")

<h2 id="ring1_filesystem_setfilecontents">Ring1_FileSystem_setFileContents</h2>
<p>Sets the contents of a file.</p>
<p><code class="block">
Ring1_Result<br/>
Ring1_FileSystem_setFileContents<br/>
&nbsp;&nbsp;(<br/>
&nbsp;&nbsp;&nbsp;&nbsp;char const *pathname,<br/>
&nbsp;&nbsp;&nbsp;&nbsp;void const *bytes,<br/>
&nbsp;&nbsp;&nbsp;&nbsp;size_t *numberOfBytes<br/>
&nbsp;&nbsp;)
</code></p>

<p>
This function sets the contents of a file.
</p>

<h3>Parameter variables</h3>
<dl>
  <dt><code class="inline">pathname</code></dt>
  <dd>The pathname of the file.</dd>

  <dt><code class="inline">bytes</code></dt>
  <dd>The array to write.</dd>
  
  <dt><code class="inline">numberOfBytes</code></dt>
  <dd>The number of Bytes in the array to write.</dd>
</dl>

<h3>Return Values</h3>
<p><code class="inline">Ring1_Result_Success</code> on success, <code class="inline">Ring1_Result_Failure</code> on failure.</p>

<h3>Post Conditions</h3>
<p>If this function fails, then it sets the <a href="@(baseurl)api/ring1-library/status-library">by-thread status variable</a>.
<p>Below is a list of failure conditions and the status codes indicating them.</p>
<dl class="parameters">
  <dt><code class="inline">Ring1_Status_InvalidArgument</code></dt>
  <dd>
    <code class="inline">pathname</code> and/or
    <code class="inline">bytes</code>,
    is
    <code class="inline">NULL</code>.
  </dd>
  
  <dt><code class="inline">Ring1_Status_EnvironmentFailed</code></dt> 
  <dd>
  File does not exist and creation failed.
  </dd>
  
  <dt><code class="inline">Ring1_Status_EnvironmentFailed</code></dt> 
  <dd>
  File exists and is not of the right category.
  </dd>
  
  <dt><code class="inline">Ring1_Status_EnvironmentFailed</code></dt> 
  <dd>
  Settings the file's content failed.
  </dd>
</dl>
<p>If this function fails, then the file's existence and contents are undetermined.</p>

@(>"./_footer.html.t")
