@{title = "Ring 1 :: Intrinsic Library"}
@{tableOfContents = "./api/ring1-library/_toc.ihtml"}
@(>"./_header.html.t")

<h2 id="ring1_intrinsic_fp_mantissabits">Ring1_Intrinsic_Fp_MantissaBits</h2>
<code class="block">
#define Ring1_Intrinsic_Fp_MantissaBits_<em>suffix</em> /* Implementation */
</code>
<p>
where <code class="inline"><em>suffix</em></code> is
either <code class="inline">f32</code> (for the type <code class="inline">float</code>)
or <code class="inline">f64</code> (for the type <code class="inline">double</code>).
</p>
<p>
Symbolic constant evaluating to a positive integer value denoting the number of mantissa bits of an IEEE754 floating-point value.
That value is 34 for <code class="inline">f32</code> and is 52 for <code class="inline">f64</code>.
</p>

@(>"./_footer.html.t")
