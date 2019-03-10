<?xml version="1.0" ?> 
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
<xsl:output method="text" indent="yes" encoding="iso-8859-1" />
<!-- xsl file to generate setting CPP file for mfc project-->



<!-- FILE -->
<xsl:template match="file">
// <xsl:value-of select="name"/>.cpp
// implementation of  settings 
// Automatic generated header file by xml->xslt = header
<xsl:text>  &#10;</xsl:text>
<!-- #include &#60;Stdafx.h&#62; -->
#include "<xsl:value-of select="name"/>.h"
#include "libini.h"

<!-- insert carriage return -->
<xsl:text>  &#10;&#10;&#10; </xsl:text>
<xsl:apply-templates select="class_settings"/>

</xsl:template> 


<!-- MAIN SETTING CLASS template -->
<xsl:template match="class_settings">

using namespace Space<xsl:value-of select="name"/>;

    <!-- istantiate global settings object-->
// global options object
<xsl:value-of select="name"/>  g_Options;
    <!-- string section key -->
<xsl:for-each select="//section">
static const char* lpsz<xsl:value-of select="name"/> = "<xsl:value-of select="name"/>";
    <!-- integer keys -->
        <!-- store the section name -->
    <xsl:variable name="namesect"><xsl:value-of select="name"/></xsl:variable>
    <xsl:for-each select="item_int">
static const char* lpsz<xsl:value-of select="$namesect"/><xsl:value-of select="name"/> = "<xsl:value-of select="$namesect"/><xsl:value-of select="name"/>";
    </xsl:for-each>
    <xsl:for-each select="item_string">
static const char* lpsz<xsl:value-of select="$namesect"/><xsl:value-of select="name"/> = "<xsl:value-of select="$namesect"/><xsl:value-of select="name"/>";
    </xsl:for-each>
</xsl:for-each>
    

//! constructor
<xsl:value-of select="name"/>::<xsl:value-of select="name"/>()
{

}

<!-- constructor of all sections -->
<xsl:variable name="parentclass"><xsl:value-of select="name"/></xsl:variable>
<xsl:for-each select="//section">
<xsl:value-of select="$parentclass"/>::<xsl:value-of select="name"/>::<xsl:value-of select="name"/>()
{
        <!-- integer initialization keys -->
        <!-- store the section name -->
    <xsl:for-each select="item_int">
    <xsl:value-of select="name"/> = <xsl:value-of select="default"/>;
    </xsl:for-each>
    <xsl:for-each select="item_string">
    <xsl:value-of select="name"/> = "<xsl:value-of select="default"/>";
    </xsl:for-each>
}

</xsl:for-each>


void Space<xsl:value-of select="name"/>::WriteProfile(const char* strIniFileName)
{
  ini_fd_t  m_pIni = ini_open(strIniFileName, "w", "#");
  if (m_pIni == 0)
       return;
       
  <xsl:for-each select="//section">
        <xsl:variable name="namesect"><xsl:value-of select="name"/></xsl:variable>
        <xsl:variable name="sectobj"><xsl:value-of select="name_obj"/></xsl:variable>
    <xsl:for-each select="item_int">
    ini_locateHeading(m_pIni, lpsz<xsl:value-of select="$namesect"/>);
    ini_locateKey(m_pIni, lpsz<xsl:value-of select="$namesect"/><xsl:value-of select="name"/>);
    ini_writeInt(m_pIni, g_Options.<xsl:value-of select="$sectobj"/>.<xsl:value-of select="name"/>);
    </xsl:for-each>
    <xsl:for-each select="item_string">
    ini_locateHeading(m_pIni, lpsz<xsl:value-of select="$namesect"/>);
    ini_locateKey(m_pIni, lpsz<xsl:value-of select="$namesect"/><xsl:value-of select="name"/>);
    ini_writeString(m_pIni, g_Options.<xsl:value-of select="$sectobj"/>.<xsl:value-of select="name"/>.c_str());
    </xsl:for-each>
  </xsl:for-each>
    ini_close(m_pIni);
  
}

void Space<xsl:value-of select="name"/>::GetProfile(const char* strIniFileName)
{
  ini_fd_t  m_pIni = ini_open(strIniFileName, "r", "#");
  int iVal;
  char buff[2048];
  <xsl:for-each select="//section">
        <xsl:variable name="namesect"><xsl:value-of select="name"/></xsl:variable>
        <xsl:variable name="sectobj"><xsl:value-of select="name_obj"/></xsl:variable>
    <xsl:for-each select="item_int">
    iVal = <xsl:value-of select="default"/>;
    if (m_pIni)
    {
        ini_locateHeading(m_pIni, lpsz<xsl:value-of select="$namesect"/>);
        ini_locateKey(m_pIni, lpsz<xsl:value-of select="$namesect"/><xsl:value-of select="name"/>);
        ini_readInt(m_pIni, &#38;iVal);
    }
    g_Options.<xsl:value-of select="$sectobj"/>.<xsl:value-of select="name"/> = iVal;
    </xsl:for-each>
    <xsl:for-each select="item_string">
    strcpy(buff, "<xsl:value-of select="default"/>");
    if (m_pIni)
    {
        ini_locateHeading(m_pIni, lpsz<xsl:value-of select="$namesect"/>);
        ini_locateKey(m_pIni, lpsz<xsl:value-of select="$namesect"/><xsl:value-of select="name"/>);
        ini_readString(m_pIni, buff, 2048);
    }
 	g_Options.<xsl:value-of select="$sectobj"/>.<xsl:value-of select="name"/> = buff;
    </xsl:for-each>
  </xsl:for-each>
  if (m_pIni)
  {
     ini_close(m_pIni);
  }
}
</xsl:template> 

<!-- SECTION -->
<xsl:template match="section">
</xsl:template> 

<!-- item int -->
<xsl:template match="section/item_int">
</xsl:template> 

<!-- item string -->
<xsl:template match="section/item_string">
</xsl:template> 


<xsl:template match="section/name">
</xsl:template> 
<xsl:template match="section/name_obj">
</xsl:template> 

</xsl:stylesheet> 