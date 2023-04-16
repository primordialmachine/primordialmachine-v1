@{title = "Ring 1 :: Intrinsic Library"}
@{tableOfContents = "./api/ring1-library/_toc.ihtml"}
@(>"./_header.html.t")

<h3 id="ring1_intrinsic_countleadingzeroes">Ring1_Intrinsic_countLeadingZeroes</h3>
<p>Computes the number of leading zeroes of the binary representation of unsigned integer value.</p>
<p><code class="block">
short<br/>
Ring1_Intrinsic_countLeadingZeroes_<em>suffix</em><br/>
&nbsp;&nbsp;(<br/>
&nbsp;&nbsp;&nbsp;&nbsp;short *result,<br/>
&nbsp;&nbsp;&nbsp;&nbsp;<em>type</em> x<br/>
&nbsp;&nbsp;)
</code></p>
<p>The following table denotes the valid combinations of <em>suffix</em> and <em>type</em></p>
<table class="table">
  <tr>
    <td><code style="inline"><em>suffix</em></code></td>
    <td><code style="inline"><em>type</em></code></td>
  </tr>

  <tr>
    <td><code style="inline">u8</code></td>
    <td><code style="inline">uint8_t</code></td>
  </tr>
  <tr>
    <td><code style="inline">u16</code></td>
    <td><code style="inline">uint16_t</code></td>
  </tr>
  <tr>
    <td><code style="inline">u32</code></td>
    <td><code style="inline">uint32_t</code></td>
  </tr>
  <tr>
    <td><code style="inline">u64</code></td>
    <td><code style="inline">uint64_t</code></td>
  </tr>

  <tr>
    <td><code style="inline">sz</code></td>
    <td><code style="inline">size_t</code></td>
  </tr>
</table>


<h4>Parameter Values</h4>
<dl class="parameters">
  <dt><code class="inline">result</code></dt><dd>A pointer to a variable.
  <code class="inline">result</code> is assigned the leading zeroes on success.
  <code class="inline">result</code> is not dereferenced on failure.</dd>
  <dt>x</dt><dd>The value value.</dd>
</dl>

<h3>Return Values</h3>
<p>
<code class="inline"><a href="@(baseurl)api/ring1-library/result-library/result-codes">Ring1_Result_Success</a></code> on success,
<code class="inline"><a href="@(baseurl)api/ring1-library/result-library/result-codes">Ring1_Result_Failure</a></code> on failure.
</p>

<h3>Post Conditions</h3>
<p>If this function fails, then it sets the <a href="@(baseurl)ring1-library\status-library">by-thread status variable</a>.</p>
<p>Below is a list of failure conditions and the status codes indicating them.</p>
<dl class="parameters">
  <dt><code class="inline">Ring1_Status_InvalidArgument</code></dt><dd><code class="inline">result</code> was <code class="inline">0</code>.</dd>
</dl>

@(>"./_footer.html.t")
