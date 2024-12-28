if (Test-Path env:VERSION) {
	$version = $env:VERSION
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