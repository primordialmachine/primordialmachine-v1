@{title = "Ring 1 :: Hash Library"}
@{tableOfContents = "./api/ring1-library/_toc.ihtml"}
@(>"./_header.html.t")

<h2 id="ring1_hash_toSz">Ring1_Hash_toSz</h2>
<p>Compute the <code class="inline">int64_t</code> hash value.</p>
<p><code class="block">
Ring1_Result<br/>
Ring1_Hash_toSz_<em>suffix</em><br/>
&nbsp;&nbsp;(<br/>
&nbsp;&nbsp;&nbsp;&nbsp;int64_t* result,<br/>
&nbsp;&nbsp;&nbsp;&nbsp;<em>type</em> value<br/>
&nbsp;&nbsp;)
</code></p>
<p>The following table denotes the valid combinations of <em>suffix</em> and <em>type</em></p>
<table class="table">
  <tr>
    <td><code style="inline"><em>suffix</em></code></td>
    <td><code style="inline"><em>type</em></code></td>
  </tr>

  <tr>
    <td><code style="inline">b</code></td>
    <td><code style="inline">bool</code></td>
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
  
  <tr>
    <td><code style="inline">f32</code></td>
    <td><code style="inline">float</code></td>
  </tr>
  <tr>
    <td><code style="inline">f64</code></td>
    <td><code style="inline">double</code></td>
  </tr>
  
  <tr>
    <td><code style="inline">p</code></td>
    <td><code style="inline">void *</code></td>
  </tr>
</table>

<p>
Computes the <code class="inline">int64_t</code> hash value of an <code class="inline"><em>type</em></code> value.
</p>

<h3>Parameter Variables</h3>
<dl class="parameters">
  <dt><code class="inline">result</code></dt>
  <dd>A pointer to a <code class="inline">int64_t</code> variable.</dd>
  <dt><code class="inline">value</code></dt>
  <dd>An <code class="inline"><em>type</em></code> value.</dd>
</dl>

<h3>Return Values</h3>
<p><code class="inline">Ring1_Result_Success</code> on success, <code class="inline">Ring1_Result_Failure</code> on failure.</p>

<h3>Post Conditions</h3>
<p>If this function fails, then it sets the <a href="@(baseurl)api/ring1-library/status-library">by-thread status variable</a>.</p>
<p>This function fails if and only if <code class="inline">result</code> is a null pointer.</p>
<p><code class="inline">*result</code> is assigned the hash value of <code class="inline">value</code> on success.</p>

@(>"./_footer.html.t")
