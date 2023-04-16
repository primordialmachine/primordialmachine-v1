@{title = "Ring 1 :: Intrinsic Library"}
@{tableOfContents = "./api/ring1-library/_toc.ihtml"}
@(>"./_header.html.t")

<h2 id="ring1_intrinsic_ispoweroftwo">Ring1_Intrinsic_isPowerOfTwo</h2>
<p>Get if a value is a power of two.</p>

<p><code class="block">
Ring1_Result<br/>
Ring1_Intrinsic_isPowerOfTwo_<em>suffix</em><br/>
&nbsp;&nbsp;(<br/>
&nbsp;&nbsp;&nbsp;&nbsp;<em>type</em> *result,<br/>
&nbsp;&nbsp;&nbsp;&nbsp;<em>type</em> *x<br/>
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

<h3>Parameter variables</h3>
<dl class="parameters">
  <dt><code class="inline">result</code></dt>
  <dd>A pointer to an <code class="inline">bool</code> variable.</dd>
  <dt><code class="inline">result</code></dt>
  <dd>The value.</dd>
</dl>

<h3>Return Values</h3>
<p>
<code class="inline"><a href="@(baseurl)api/ring1-library/result-library/result-codes">Ring1_Result_Success</a></code> on success,
<code class="inline"><a href="@(baseurl)api/ring1-library/result-library/result-codes">Ring1_Result_Failure</a></code> on failure.
</p>

<h3>Post Conditions</h3>
<p>If this function fails, then it sets the <a href="@(baseurl)api/ring1-library/status-library">by-thread status variable</a>.
<p>Below is a list of failure conditions and the status codes indicating them.</p>
<dl class="parameters">
  <dt><code class="inline">Ring1_Status_InvalidArgument</code></dt><dd><code class="inline">y</code> was <code class="inline">0</code>.</dd>
</dl>
<p>If this function fails, <code class="inline">result</code> is not dereferenced.</p>

<p>If this function succeeds, <code class="inline">*result</code> is assigned <code class="inline">true</code> if <code class="inline">x</code>
is a power of two and is assigned <code class="inline">false</code> otherwise.

<h3>Remarks</h3>
<p>In particular, this function considers <code class="inline">0</code> not as a power of two.</p>

@(>"./_footer.html.t")
