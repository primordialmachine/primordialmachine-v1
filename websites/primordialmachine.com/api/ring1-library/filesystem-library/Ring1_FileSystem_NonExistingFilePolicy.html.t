@{title = "Ring 1 :: File System Library"}
@{tableOfContents = "./api/ring1-library/_toc.ihtml"}
@(>"./_header.html.t")

<h2 id="ring1_filesystem_nonexistingfilepolicy">Ring1_FileSystem_NonExistingFilePolicy</h2>
<p>An enumeration of policies for handling the situation in which a non-existing file is opened.</p>
<p><code class="block">
typedef Ring1_FileSystem_NonExistingFilePolicy {<br/>
&nbsp;&nbsp;...<br/>
} Ring1_FileSystem_NonExistingFilePolicy;
</code></p>

<p>
An enumeration of policies for handling the situation in which a non-existing file is opened.
</p>

<h3>Enumeration Elements</h3>
<dl>
  <dt><code class="inline">Ring1_FileSystem_NonExistingFilePolicy_Fail</code></dt>
  <dd>
  Fail if the file does not exist.
  </dd>

  <dt><code class="inline">Ring1_FileSystem_NonExistingFilePolic_Create</code></dt>
  <dd>
  Create the file if it does not exist.
  </dd>
</dl>

@(>"./_footer.html.t")
