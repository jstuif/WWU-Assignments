#Joshua Stuifbergen
#3/16/19
#CISS 360
#Assignment 5 Service Monitor

param ([string]$option)

#$env:UserName     ---switch back once script is done'
#Retrieves all running services to create whitelist, a few service are manually removed after creation
#Get-Service | Where-Object {$_.Status -EQ "Running"} | Select-Object -Property Name,StartType | `
#Export-Csv C:\Users\<User>\Desktop\list.Csv 

$list = Import-Csv C:\Users\<User>\Desktop\list.Csv

#Let the user choose between a whitelist they created or a provided default whitelist
#
#function whitelist{
#    $userInput = Read-Host "User personal whitelist or default whitelist? personal/default "
#    if($userInput -eq 'personal'){
#        $userWL = Read-Host "Enter in exact path to whitelist file "
#        $userWhiteList = Import-Csv -Path $userWL
#   } else {
#         C:\Users\<User>\Desktop\list.Csv
#    }   
#}

#Compares the whitelist to the current running services list and prints out the services that do not match.
function checkRunningService {
    #Grabs list of current running services
    Get-Service | Where-Object {$_.Status -EQ "Running"} | Select-Object -Property Name,StartType | `
    Export-Csv C:\Users\<User>\Desktop\CurrentRunningList.Csv 

    #Stored variables for the whitelist(list) and current running list
    $list = Import-Csv -Path C:\Users\<User>\Desktop\list.Csv 
    $currentRunningList = Import-Csv -Path C:\Users\<User>\Desktop\CurrentRunningList.Csv

    #------------Compares the difference between list and CurrentRunningList--------------
    #prints out services that are different
    Write-Host ""
    Write-Host "Services that are not on the Whitelist:"
    Compare-Object $list $currentRunningList -Property Name | Get-Service | Format-Table Name, Status, StartType
}

#A new list of all StartType 'Automatic' are pulled from the whitelist and compared a list of current running services
#If the service name is matched and the StartType is not Automatic, it lets the user decide whether to change
#the StartType to 'Automatic'
function checkAutoStart {
    #Grabs list of current running services
    Get-Service | Where-Object {$_.Status -EQ "Running"} | Select-Object -Property Name,StartType | `
    Export-Csv C:\Users\<User>\Desktop\CurrentRunningList.Csv 

    #All lines that have StartType Automatic piped to this file, listAuto
    $list | Where-Object {$_ -match 'Automatic'} | Export-Csv  C:\Users\<User>\Desktop\listAuto.Csv
    $listAuto = Import-Csv C:\Users\<User>\Desktop\listAuto.Csv

    #Stored variables for the whitelist(list) and current running list
    #$listAuto = Import-Csv -Path C:\Users\<User>\Desktop\listAuto.Csv 
    $currentRunningList = Import-Csv -Path C:\Users\<User>\Desktop\CurrentRunningList.Csv

    #------------Compares whether StartType of services is manual or automatic between listAuto and CurrentRunningList--------------
    Write-Host ""
    Write-Host "Services whose StartType is Manual but should be set to Autostart:"

    #grab each name at each line for current running services
    foreach($line in $currentRunningList.Name){
            #if name matches from listAuto, copy name
            if($listAuto.Name | Select-String -SimpleMatch $line){ 
                #grabs StartType to check if it is already Automatic
                $testStartType = Get-Service -Name $line | select StartType
                #checks if it is running on Automatic
                if($testStartType | Select-String -SimpleMatch "@{StartType=Automatic}"){
                    Write-Host $line "already automatic"
                } elseif(($change = Read-Host "Make the $line service Automatic? y/n ") -eq 'y'){ 
                    Set-Service -Name $line -StartupType "Automatic"
                    Write-Host "---------"$line "is now set to Automatic"
                } elseif ($change -eq 'n'){
                    Write-Host ""
                    Write-Host "Did not change "$line "to Automatic"
                    Write-Host ""
                } else{
                   Write-Host ""
                   Write-Host "Bad Input"
                    Write-Host ""
                }
            }
    }  
}

#Add new service to whitelist
function addService {
    if(($add = Read-Host "Add service to whitelist? y/n ") -eq 'y'){
        $newService = Read-Host "Enter a service "    
            $newService = Get-Service -Name $newService | Select -Property Name,StartType
            #$newService
            $newService | Export-Csv C:\Users\<User>\Desktop\newServiceList.Csv
            $From = Get-Content C:\Users\<User>\Desktop\newServiceList.Csv | Select-String -Pattern "$newService","manual"
            $To = Add-Content C:\Users\<User>\Desktop\list.Csv -Value $From
            $To
      
    } elseif($add -eq 'n'){
        Write-Host "No new service added"
    } else {
        Write-Host "Bad Input"
    }
}

#Script use options
function helperPrompt {

    Write-Host "Enter '.\Assignment5.ps1 -option' follow by a parameter"
    Write-Host "Check current running services against whitelist: rs" 
    Write-Host "Check if services StartTpe are set to Automatic according to the whitelist: ca"
    Write-Host "Add service to whitelist: add"
    Write-Host "Review Help Menu: help"
    
}

#Script Auto Helper Prompt
function autoHelperPrompt {
    if([string]::IsNullOrEmpty($option)){
        helperPrompt
    } elseif ($Args[0] -eq "help"){
        helperPrompt
    } else {
        helperPrompt
    }
}

Switch ($option) {
    default {autoHelperPrompt}
    help {helperPrompt}
    #wl {whitelist}
    rs {checkRunningService}
    ca {checkAutoStart}
    add {addService}
}


    #Creates list of running services that include the Name and StartType properties, temp file for the listAuto file
    #Get-Service | Where-Object {$_.Status -eq "Running"; $_.StartType -eq "AutoStart"} | Select-Object -Property Name,StartType | `
    #Export-Csv C:\Users\<User>\Desktop\tempListAuto.Csv 

    #Variable for the tempListAuto file to be used for listAuto file
    #$lineAutoCheck = Import-Csv -Path C:\Users\<User>\Desktop\tempListAuto.Csv 
