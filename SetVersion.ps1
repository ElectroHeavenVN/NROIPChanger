if (Test-Path env:VERSION) {
	$version = $env:VERSION
	if (Test-Path Properties\AssemblyInfo.cs) {
		$assemblyInfo = Get-Content -Path Properties\AssemblyInfo.cs
		if ($version -eq "nightly") {
			$assemblyInfo = $assemblyInfo -replace "^\[assembly: AssemblyVersion\(`"(.*?)`"\)]", ('[assembly: AssemblyVersion("0.0.0.0")]')
			$assemblyInfo = $assemblyInfo -replace "^\[assembly: AssemblyFileVersion\(`"(.*?)`"\)]", ('[assembly: AssemblyFileVersion("0.0.0.0")]')
			$assemblyInfo = $assemblyInfo -replace "^\[assembly: AssemblyInformationalVersion\(`"(.*?)`"\)]", ('[assembly: AssemblyInformationalVersion("0.0.0-nightly")]')
		}
		else {
			$assemblyInfo = $assemblyInfo -replace "^\[assembly: AssemblyVersion\(`"(.*?)`"\)]", ('[assembly: AssemblyVersion("' + $env:VERSION + '.0")]')
			$assemblyInfo = $assemblyInfo -replace "^\[assembly: AssemblyFileVersion\(`"(.*?)`"\)]", ('[assembly: AssemblyFileVersion("' + $env:VERSION + '.0")]')        
			$assemblyInfo = $assemblyInfo -replace "^\[assembly: AssemblyInformationalVersion\(`"(.*?)`"\)]", ('[assembly: AssemblyInformationalVersion("' + $env:VERSION + '")]')
		}
		$assemblyInfo | Set-Content -Path Properties\AssemblyInfo.cs -Encoding UTF8
	}
	if (Test-Path Resource.rc) {
		$resource = Get-Content -Path Resource.rc
		if ($version -eq "nightly") {
			$resource = $resource -replace "FILEVERSION ([0-9]*?),0,0,0", ('FILEVERSION 0,0,0,0')
			$resource = $resource -replace "PRODUCTVERSION ([0-9]*?),0,0,0", ('PRODUCTVERSION 0,0,0,0')
			$resource = $resource -replace 'VALUE "FileVersion", "(.*?)"', ('VALUE "FileVersion", "0.0.0.0"')
			$resource = $resource -replace 'VALUE "ProductVersion", "(.*?)"', ('VALUE "ProductVersion", "0.0.0-nightly"')
		}
		else {
			$resource = $resource -replace "FILEVERSION ([0-9]*?),0,0,0", ('FILEVERSION ' + $env:VERSION.Replace('.', ',') + ',0')
			$resource = $resource -replace "PRODUCTVERSION ([0-9]*?),0,0,0", ('PRODUCTVERSION ' + $env:VERSION.Replace('.', ',') + ',0')
			$resource = $resource -replace 'VALUE "FileVersion", "(.*?)"', ('VALUE "FileVersion", "' + $env:VERSION + '.0"')
			$resource = $resource -replace 'VALUE "ProductVersion", "(.*?)"', ('VALUE "ProductVersion", "' + $env:VERSION + '.0"')
		}
		$resource | Set-Content -Path Resource.rc -Encoding UTF8
	}
}