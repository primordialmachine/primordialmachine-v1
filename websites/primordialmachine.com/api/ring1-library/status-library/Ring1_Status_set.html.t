@{title = "Ring 1 :: Status Library"}
@{tableOfContents = "./api/ring1-library/_toc.ihtml"}
@(>"./_header.html.t")

<h2 id="ring1_status_set">Ring1_setStatus</h2>
<p>Set the by-thread status variable.</p>
<p><code class="block">
void<br/>
Ring1_Status_set<br/>
&nbsp;&nbsp;(<br/>
&nbsp;&nbsp;&nbsp;&nbsp;Ring1_Status status<br/>
&nbsp;&nbsp;)
</code></p>

<p>
This function sets the by-thread status variable.
</p>

<h3>Parameter variables</h3>
<dl class="parameters">
  <dt><code class="inline">status</code></dt><dd>The value to be assigned to the by-thread status variable.</dd>
</dl>

@(>"./_footer.html.t")
