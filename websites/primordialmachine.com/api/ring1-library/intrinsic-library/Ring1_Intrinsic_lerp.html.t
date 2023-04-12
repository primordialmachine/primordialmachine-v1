<h3 id="mkx_intrinsic_lerp">Mkx_Intrinsic_lerp</h3>
<p>Lineary interpolate between to floating-point values.</p>
<p><code class="block">
(float|double)<br/>
Mkx_Intrinsic_lerp_(f32|f64)<br/>
&nbsp;&nbsp;(<br/>
&nbsp;&nbsp;&nbsp;&nbsp;(float|double) t,<br/>
&nbsp;&nbsp;&nbsp;&nbsp;(float|double) x,<br/>
&nbsp;&nbsp;&nbsp;&nbsp;(float|double) y<br/>
&nbsp;&nbsp;)
</code></p>

<p>
This function lineary interpolates between the floating-point value <code class="inline">x</code> and the floating-point value <code class="inline">y</code>
using the interpolation factor <code class="inline">t</code> i.e. computes <code class="inline">(1 - t) * x + t * y</code>. The parameter <code class="inline">
t</code> is clamped to the range 0 and 1 as described in <a href="@(baseurl)utility-libraries/intrinsic-library#mkx_intrinsic_clamp"><code class="inline">Mkx_Intrinsic_clamp</code></a>.
</p>

<p>
By the above, if <code class="inline">t</code>, <code class="inline">x</code>, or <code class="inline">y</code> is not a number,
then this function returns not a number.
</p>


<h4>Parameter Values</h4>
<dl class="parameters">
  <dt><code class="inline">t</code></dt><dd>The interpolation factor.</dd>
  <dt><code class="inline">x</code></dt><dd>The 1st value.</dd>
  <dt><code class="inline">y</code></dt><dd>The 2nd value.</dd>
</dl>

<h4>Return value</h4>
<p>The interpolated value.</p>
