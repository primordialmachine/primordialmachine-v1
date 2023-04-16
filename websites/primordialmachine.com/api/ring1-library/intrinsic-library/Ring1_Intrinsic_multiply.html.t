@{title = "Ring 1 :: Intrinsic Library"}
@{tableOfContents = "./api/ring1-library/_toc.ihtml"}
@(>"./_header.html.t")

<h2 id="ring1_intrinsic_multiply">Ring1_Intrinsic_multiply</h2>
<p>Compute the producct of two values detecting numeric overflows.</p>

<p><code class="block">
Ring1_Result<br/>
Ring1_Intrinsic_multiply_<em>suffix</em><br/>
&nbsp;&nbsp;(<br/>
&nbsp;&nbsp;&nbsp;&nbsp;<em>type</em> *result,<br/>
&nbsp;&nbsp;&nbsp;&nbsp;<em>type</em> x,<br/>
&nbsp;&nbsp;&nbsp;&nbsp;<em>type</em> y<br/>
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
</table>

<h3>Parameter Variables</h3>
<dl class="parameters">
  <dt><code class="inline">x</code></dt>
  <dd>The first value aka multiplicand.</dd>
  <dt><code class="inline">y</code></dt>
  <dd>The second value aka multiplier.</dd>
  <dt><code class="inline">result</code></dt>
  <dd>A pointer to a variable.
  For the assigned value see remarks section.</dd>
</dl>

<h3>Return Values</h3>
<p>
<code class="inline"><a href="@(baseurl)api/ring1-library/result-library/result-codes">Ring1_Result_Success</a></code> on success,
<code class="inline"><a href="@(baseurl)api/ring1-library/result-library/result-codes">Ring1_Result_Failure</a></code> on failure.
</p>

<h3>Post Conditions</h3>
<p>If this function fails, then it sets the <a href="@(baseurl)api/ring1-library/status-library">by-thread status variable</a>.</p>
<p>Below is a list of failure conditions and the status codes indicating them.</p>
<dl class="parameters">
  <dt><code class="inline">Ring1_Status_InvalidArgument</code></dt><dd><code class="inline">result</code> was <code class="inline">NULL</code>.</dd>
  <dt><code class="inline">Ring1_Status_NumericOverflow</code></dt><dd>a numeric overflow occurred.</dd>
</dl>

<h3>Remarks</h3>
<p>For the function variants for uintn_t and size_t,
the value assigned to the variable are the lower n bits of the mathematical sum of the addend and the augend.
(This means x + y is reduced modulo MAX + 1 where MAX is UINTn_MAX or SIZE_MAX, respectively.</p>
<p>For the function variants for intn_t,
the value assigned to the variable are the lower n bits of the 2's complements product of the multiplier and the multiplicand.</p>
<p>Consequently, these functions can be used to perform safe multiplication of signed and unsigned integers.</p>

@(>"./_footer.html.t")
