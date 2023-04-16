@{title = "Ring 1 :: Intrinsic Library"}
@{tableOfContents = "./api/ring1-library/_toc.ihtml"}
@(>"./_header.html.t")

<h2 id="ring1_intrinsic_atomicincrement_s32">Ring1_Intrinsic_atomicIncrement_s32</h2>
<p>Atomically increment a variable value.</p>
<p><code class="block">
int32_t<br/>
Ring1_Intrinsic_atomicallyDecrement_s32<br/>
&nbsp;&nbsp;(<br/>
&nbsp;&nbsp;&nbsp;&nbsp;int32_t *variable<br/>
&nbsp;&nbsp;)
</code></p>

<p>
Atomically increments the variable value <code>*variable</code>.
Effectively performs
<code class="block">
return ++(*variable);
</code>
</p>

<h3>Parameter Values</h3>
<dl class="parameters">
  <dt>variable</dt>
  <dd>A pointer to the variable.</dd>
</dl>

<h3>Return value</h3>
<p>The incremented value.</p>

@(>"./_footer.html.t")
