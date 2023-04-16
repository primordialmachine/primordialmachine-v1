@{title = "Ring 1 :: Intrinsic Library"}
@{tableOfContents = "./api/ring1-library/_toc.ihtml"}
@(>"./_header.html.t")

<h2 id="ring1_intrinsic_clamp">Ring1_Intrinsic_clamp</h2>
<p>Clamp a value to a range.</p>
<p><code class="block">
Ring1_Result<br/>
Ring1_Intrinsic_clamp_<em>suffix</em><br/>
&nbsp;&nbsp;(<br/>
&nbsp;&nbsp;&nbsp;&nbsp;<em>type</em>* result,<br/>
&nbsp;&nbsp;&nbsp;&nbsp;<em>type</em> x,<br/>
&nbsp;&nbsp;&nbsp;&nbsp;<em>type</em> minimum,<br/>
&nbsp;&nbsp;&nbsp;&nbsp;<em>type</em> maximum<br/>
&nbsp;&nbsp;)
</code></p>
<p>The following table denotes the valid combinations of <em>suffix</em> and <em>type</em></p>
<table class="table">
  <tr>
    <td><code style="inline"><em>suffix</em></code></td>
    <td><code style="inline"><em>type</em></code></td>
  </tr>
  
  <tr>
    <td><code style="inline">f32</code></td>
    <td><code style="inline">float</code></td>
  </tr>
  <tr>
    <td><code style="inline">f64</code></td>
    <td><code style="inline">double</code></td>
  </tr>

  <!--
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
    <td><code style="inline">s8</code></td>
    <td><code style="inline">int8_t</code></td>
  </tr>
  <tr>
    <td><code style="inline">s16</code></td>
    <td><code style="inline">int16_t</code></td>
  </tr>
  <tr>
    <td><code style="inline">s32</code></td>
    <td><code style="inline">int32_t</code></td>
  </tr>
  <tr>
    <td><code style="inline">s64</code></td>
    <td><code style="inline">int64_t</code></td>
  </tr>

  <tr>
    <td><code style="inline">sz</code></td>
    <td><code style="inline">size_t</code></td>
  </tr>
  -->
</table>

<p>
This function clamps a value to the range 0 (inclusive) and 1 (inclusive):
</p>
<ul class="cutelist">
  <li>a value smaller than <code class="inline">minimum</code> is mapped to <code class="inline">minimum</code>.</li>
  <li>a value greater than <code class="inline">maximum</code> is mapped to <code class="inline">maximum</code>.</li>
  <li>negative infinity is mapped to <code class="inline">minimum</code>.</li>
  <li>positive infinity is mapped to <code class="inline">maximum</code>.</li>
</ul>

<h3>Parameter Values</h3>
<dl class="parameters">
  <dt><code class="inline">result</code></dt>
  <dd>A pointer to a <code class="inline"><em>type</em> variable.</dd>
  <dt><code class="inline">x</code></dt>
  <dd>The value to clamp.</dd>
  
  <dt><code class="inline">minimum</code></dt>
  <dd>The minimum of the range.</dd>
  <dt><code class="inline">maximum</code></dt>
  <dd>The maximum of the range.</dd>
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
  <dt><code class="inline">Ring1_Status_InvalidArgument</code></dt>
  <dd><code class="inline">result</code> was <code class="inline">NULL</code>.</dd>
  
  <dt><code class="inline">Ring1_Status_InvalidArgument</code></dt>
  <dd>
  <code class="inline">x</code>, <code class="inline">minimum</code>, and/or <code class="inline">maximum</code> is not a number</code>.
  </dd>
  
  <dt><code class="inline">Ring1_Status_InvalidArgument</code></dt>
  <dd><code class="inline">minimum</code> is greater than <code class="inline">maximum</code>.</dd>
</dl>

<p>If this function succeeds, then <code class="inline">*result</code> was assigned the clamped value.</p>

@(>"./_footer.html.t")
