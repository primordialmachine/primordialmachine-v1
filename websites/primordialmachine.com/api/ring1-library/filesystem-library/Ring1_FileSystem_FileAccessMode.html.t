@{title = "Ring 1 :: File System Library"}
@{tableOfContents = "./api/ring1-library/_toc.ihtml"}
@(>"./_header.html.t")

<h2 id="ring1_filesystem_fileaccessmode">Ring1_FileSystem_FileAccessMode</h2>
<p>Enumeration of a file access mode.</p>
<p><code class="block">
typedef Ring1_FileSystem_FileAccessMode {<br/>
&nbsp;&nbsp;...<br/>
} Ring1_FileSystem_FileAccessMode;
</code></p>

<p>
An enumeration of file access modes.
The values of this enumeration can be or-ed together.
</p>

<h3>Enumeration Elements</h3>
<dl>
  <dt><code class="inline">Ring1_FileSystem_FileAccessMode_Read</code></dt>
  <dd>
  Read access. Can be combined with <code class="inline">Ring1_FileSystem_FileAccessMode_Write</code>.
  </dd>

  <dt><code class="inline">Ring1_FileSystem_FileAccessMode_Write</code></dt>
  <dd>
  Write access. Can be combined with <code class="inline">Ring1_FileSystem_FileAccessMode_Read</code>.
  </dd>
  
  <dt><code class="inline">Ring1_FileSystem_FileAccessMode_ReadWrite</code></dt>
  <dd>
  Both read and write access.
  Alias for <code class="inline">Ring1_FileSystem_FileAccessMode_Read|Ring1_FileSystem_FileAccessMode_Write</code>.
  </dd>
  
  <dt><code class="inline">Ring1_FileSystem_FileAccessMode_WriteRead</code></dt>
  <dd>
  Alias of <code class="inline">Ring1_FileSystem_FileAccessMode_ReadWrite</code>.
  </dd>
</dl>

@(>"./_footer.html.t")
