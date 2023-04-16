@{title = "Ring 1 :: Intrinsic Library"}
@{tableOfContents = "./api/ring1-library/_toc.ihtml"}
@(>"./_header.html.t")

<h2 id="ring1_intrinsic_atomicget_s32">Ring1_Intrinsic_atomicGet_s32</h2>
<p>Atomically gets the value of a variable.</p>
<p><code class="block">
int32_t<br/>
Ring1_Intrinsic_atomicallyGet_s32<br/>
&nbsp;&nbsp;(<br/>
&nbsp;&nbsp;&nbsp;&nbsp;int32_t *variable<br/>
&nbsp;&nbsp;)
</code></p>

<p>
Atomically gets the value of the <code>*variable</code>.
</p>

<h3>Parameter Values</h3>
<dl class="parameters">
  <dt>variable</dt>
  <dd>A pointer to the variable.</dd>
</dl>

<h4>Return value</h4>
<p>The value of the variable.</p>

@(>"./_footer.html.t")
