@{title = "Ring 1 :: Time Library"}
@{tableOfContents = "./api/ring1-library/_toc.ihtml"}
@(>"./_header.html.t")

<h2 id="ring1_time_getnowseconds">Ring1_Time_getNowSeconds</h2>
<p>Get the time, in seconds, since the start of the system.</p>
<p><code class="block">
Ring1_Result<br/>
Ring1_Time_getNowSeconds<br/>
&nbsp;&nbsp;(<br/>
&nbsp;&nbsp;&nbsp;&nbsp;<em>type</em> *result<br/>
&nbsp;&nbsp;)
</code></p>
<p>The following table denotes the valid combinations of <em>suffix</em> and <em>type</em></p>
<table class="table">
  <tr>
    <td><code style="inline"><em>suffix</em></code></td>
    <td><code style="inline"><em>type</em></code></td>
  </tr>

  <tr>
    <td><code style="inline">u64</code></td>
    <td><code style="inline">uint64_t</code></td>
  </tr>

  <tr>
    <td><code style="inline">f32</code></td>
    <td><code style="inline">float</code></td>
  </tr>
</table>

<p>
This function gets the time, in seconds, since the start of the system.
</p>

<h3>Parameter variables</h3>
<dl class="parameters">
  <dt><code class="inline">result</code></dt><dd>A pointer to a <code class="inline"><em>type</em></code> variable.</dd>
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

<p>
If this function succeeds, <code class="inline">*result</code> is assigned the time, in seconds, since the start of the system.
Note that this value wraps around if the time span from the start of the system to now exceeds the representable range of the type <em>type</em>.
</p>

@(>"./_footer.html.t")
