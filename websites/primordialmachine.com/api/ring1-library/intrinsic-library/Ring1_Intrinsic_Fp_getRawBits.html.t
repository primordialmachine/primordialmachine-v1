@{title = "Ring 1 :: Intrinsic Library"}
@{tableOfContents = "./api/ring1-library/_toc.ihtml"}
@(>"./_header.html.t")

<h2 id="ring1_Intrinsic_fp_getrawbits">Ring1_Intrinsic_Fp_getRawBits</h2>
<p>Get the raw bits of a IEEE754 bit floating-point number value.</p>
<p><code class="block">
Ring1_Result<br/>
Ring1_Intrinsic_Fp_getRawBits_<em>suffix</em><br/>
&nbsp;&nbsp;(<br/>
&nbsp;&nbsp;&nbsp;&nbsp;<em>resultType</em>* result,<br/>
&nbsp;&nbsp;&nbsp;&nbsp;<em>valuetype</em> value<br/>
&nbsp;&nbsp;)
</code></p>
<p>The following table denotes the valid combinations of <em>suffix</em> and <em>type</em></p>
<table class="table">
  <tr>
    <td><code style="inline"><em>suffix</em></code></td>
    <td><code style="inline"><em>resultType</em></code></td>
    <td><code style="inline"><em>valueType</em></code></td>
  </tr>

  <tr>
    <td><code style="inline">f32</code></td>
    <td><code style="inline">uint32_t</code></td>
    <td><code style="inline">float</code></td>
  </tr>
  <tr>
    <td><code style="inline">f64</code></td>
    <td><code style="inline">uint64_t</code></td>
    <td><code style="inline">double</code></td>
  </tr>
</table>

<p>
This function gets the bits of the IEEE754 bit floating-point number value <code class="inline">value</code>.
</p>

<h3>Parameter Variables</h3>
<dl class="parameters">
  <dt><code class="inline">resiöt</code></dt><dd>A pointer to a <code class="inline"><em>result</em></code> variable.</dd>
  <dt><code class="inline">value</code></dt><dd>A <code class="inline"><em>value</em></code> variable.</dd>
</dl>

<h3>Post Conditions</h3>
<p>If this function fails, then it sets the <a href="@(baseurl)api/ring1-library/status-library">by-thread status variable</a>.
<p>Below is a list of failure conditions and the status codes indicating them.</p>
<dl class="parameters">
  <dt><code class="inline">Ring1_Status_InvalidArgument</code></dt><dd><code class="inline">result</code> was <code class="inline">NULL</code>.</dd>
</dl>
<p>If this function fails, <code class="inline">result</code> is not dereferenced.</p>
<p>If this function succeeds, <code class="inline">result</code> is assigned the raw bits of the IEEE754 floating-point value
<code class="inline">value</code>.</p>

<h3>Return Values</h3>
<p>
<code class="inline"><a href="@(baseurl)api/ring1-library/result-library/result-codes">Ring1_Result_Success</a></code> on success,
<code class="inline"><a href="@(baseurl)api/ring1-library/result-library/result-codes">Ring1_Result_Failure</a></code> on failure.
</p>

@(>"./_footer.html.t")
