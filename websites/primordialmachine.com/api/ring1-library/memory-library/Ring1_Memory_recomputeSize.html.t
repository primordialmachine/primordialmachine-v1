@{title = "Ring 1 :: Memory Library"}
@{tableOfContents = "./api/ring1-library/_toc.ihtml"}
@(>"./_header.html.t")

<h2 id="ring1_memory_recomputeSize">Ring1_Memory_recomputeSize</h2>
<p>Recompute the size of a memory block.</p>
<p><code class="block">
Ring1_Result<br/>
Ring1_Memory_recomputeSize_<em>suffix</em><br/>
&nbsp;&nbsp;(<br/>
&nbsp;&nbsp;&nbsp;&nbsp;<em>type</em> *result,<br/>
&nbsp;&nbsp;&nbsp;&nbsp;<em>type</em> min,<br/>
&nbsp;&nbsp;&nbsp;&nbsp;<em>type</em> max,<br/>
&nbsp;&nbsp;&nbsp;&nbsp;<em>type</em> old,<br/>
&nbsp;&nbsp;&nbsp;&nbsp;<em>type</em> additional,<br/>
&nbsp;&nbsp;&nbsp;&nbsp;<em>type</em> saturate<br/>
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
<p>
This function computes a new size for a memory block given its old size and a minimum increase in size.
This new size is greater than or equal to the minimum increase in size.
</p>

<p>
This algorithm runs under the assumption that memory blocks are used as dynamic arrays.
The goal here is to balance the number of growth operations with the growth per growth operation.
</p>

<h3>Parameter variables</h3>
<dl class="parameters">
  <dt><code class="inline">result</code></dt><dd>A pointer to a <code class="inline"><em>type</em></code> variable.</dd>
  <dt><code class="inline">min</code></dt><dd>The minimal value to compute.</dd>
  <dt><code class="inline">max</code></dt><dd>The maximal value to compute.</dd>
  <dt><code class="inline">old</code></dt><dd>The old value.</dd>
  <dt><code class="inline">additional</code></dt><dd>The additional size.</dd>
  <dt><code class="inline">saturate</code></dt><dd>Wether saturation should be performed or not.</dd>
</dl>

<h3>Return Values</h3>
<p><code class="inline">Ring1_Result_Success</code> on success, <code class="inline">Ring1_Result_Failure</code> on failure.</p>

<h3>Post Conditions</h3>
<p>If this function fails, then it sets the <a href="@(baseurl)api/ring1-library/status-library">by-thread status variable</a>.
<p>Below is a list of failure conditions and the status codes indicating them.</p>
<dl class="parameters">
  <dt><code class="inline">Ring1_Status_InvalidArgument</code></dt>
  <dd>
  <p>if any of the following conditions is true</p>
  <ul class="parameters">
    <li><code class="inline">result</code> was <code class="inline">0</code></li>
    <li><code class="inline">min &gt; max</code></li>
    <li><code class="inline">old &lt; min</code></li>
    <li><code class="inline">old &gt; max</code></li>
    <li><code class="inline">min</code> is negative</li>
    <li><code class="inline">additional</code> is negative</li>
  </ul>
  </dd>
  <dt><code class="inline">Ring1_Status_NotExists</code></dt>
  <dd>if the value is not representable by <code>type</code> values</dd>
</dl>
<p>If this function fails, <code class="inline">result</code> is not dereferenced.</p>

<p>If this function succeeds, <code class="inline">*result</code> is assigned a value which is computed as follows:</p>
<ul>
  <li>If <code class="inline">saturate</code> is <code class="inline">false</code> compute the least value \(x\) such that
    <ul>
      <li>\(x \ge old + new\)</li>
      <li>\(min \le x \le max\)</li>
      <li>\(x\) is a power of two.</li>
    </ul>
   </li>
   <li>If <code class="inline">saturate</code> is <code class="inline">true</code> compute the least value \(x\) such that
    <ul>
      <li>\(x \ge old + new\)</li>
      <li>\(min \le x \le max\)</li>
      <li>\(x\) is a power of two or \(x = max\).</li>
    </ul>
  </li>
</p>

@(>"./_footer.html.t")
