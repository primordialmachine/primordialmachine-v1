@{title = "Ring 1 :: File System Library"}
@{tableOfContents = "./api/ring1-library/_toc.ihtml"}
@(>"./_header.html.t")

<h2 id="ring1_filesystem_existingfilepolicy">Ring1_FileSystem_ExistingFilePolicy</h2>
<p>An enumeration of policies for handling the situation in which an existing file is opened.</p>
<p><code class="block">
typedef Ring1_FileSystem_ExistingFilePolicy {<br/>
&nbsp;&nbsp;...<br/>
} Ring1_FileSystem_ExistingFilePolicy;
</code></p>

<p>
An enumeration of policies for handling the situation in which an existing file is opened.
</p>

<h3>Enumeration Elements</h3>
<dl>
  <dt><code class="inline">Ring1_FileSystem_ExistingFilePolicy_Retain</code></dt>
  <dd>
  Retain the file.
  </dd>

  <dt><code class="inline">Ring1_FileSystem_ExistingFilePolic_Truncate</code></dt>
  <dd>
  Truncate the file.
  </dd>
</dl>

@(>"./_footer.html.t")
