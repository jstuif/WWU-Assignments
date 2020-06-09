#Joshua Stuifbergen
#3/15/19
#CISS 360
#Assignment 4 PowerShell Script

param ( [string]$option)

#Create a new user account or delete a user account
function userAddDel {
    $Choice = Read-Host "Create or delete a user account: 'c' for create and 'd' for delete "
    if($Choice -eq 'c'){
        $CreateNum = Read-Host "How many user to create? "
        for($i = 1; $i -le $CreateNum; $i++){
            Write-Host "Create a user"
            $Username = Read-Host "Enter a Username "
            $Password_SecString = Read-Host "Enter a Password" -AsSecureString
            $Name = Read-Host "Enter Full Name"
            New-LocalUser $Username -Password $Password_SecString -FullName $name -Description "Temp Account"
        }
    } elseif ($Choice -eq 'd'){
        $CreateNum = Read-Host "How many user to delete? "
        for($i = 1; $i -le $CreateNum; $i++){
            Write-Host "Delete a user"
            $Username = Read-Host "Enter a Username "
            Remove-LocalUser -Name $Username
            Write-Host $Username "Deleted"
        }
    } else {
        Write-Host ""
        Write-Host "--------Incorrect Parameter--------"
        Write-Host ""
        helperPrompt
    }
}

#Create a new group account or delete a group
function groupAddDel {
    $Choice = Read-Host "Create or delete Group: 'c' for create and 'd' for delete "
    if($Choice -eq 'c'){
        $CreateNum = Read-Host "How many groups to create? "
        for($i = 1; $i -le $CreateNum; $i++){
            Write-Host "Create a new Group"
            $Groupname = Read-Host "Enter a Group name to Create "
            $Descript = Read-Host "Add a description"
            New-LocalGroup -Name $Groupname -Description $Descript
        }
    } elseif ($Choice -eq 'd'){
        $CreateNum = Read-Host "How many groups to delete? "
        for($i = 1; $i -le $CreateNum; $i++){
            Write-Host "Delete Group"
            $Groupname = Read-Host "Enter a Group name to Delete "
            Remove-LocalUser -Name $Groupname
            Write-Host $Groupname "Deleted"
        }
    } else {
        Write-Host ""
        Write-Host "--------Incorrect Parameter--------"
        Write-Host ""
        helperPrompt
    }
}

#Add or remove user from Admin Group
function adminPriviledge {
    $Choice = Read-Host "Add or Remove User from Admin Group: 'a' for add and 'r' for remove "
    if($Choice -eq 'a'){
        Write-Host "Add User to Admin Group"
        $Username = Read-Host "Enter a User Name to Add to Admin Group "
        Add-LocalGroupMember -Group "Administrators" -Member $Username
        Write-Host $Username "Added to Admin Group"
    } elseif ($Choice -eq 'r'){
        Write-Host "Remove User from Admin Group"
        $Username = Read-Host "Enter a User Name to Remove from Admin Group "
        Remove-LocalGroupMember -Group "Administrators" -Member $Username
        Write-Host $Username "Removed from Admin Group"
    } else {
        Write-Host ""
        Write-Host "--------Incorrect Parameter--------"
        Write-Host ""
        helperPrompt
    }
}

#Script use options
function helperPrompt {
    Write-Host "Enter '.\Assignment4b.ps1 -option' follow by a parameter"
    Write-Host "Add or Delete User: user"
    Write-Host "Review Help Menu: help"
    Write-Host "Create or Delete group: group"
    Write-Host "Join or Remove User from Admin Group: admin"
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

#Option choices for script
Switch ($option) {
    default {autoHelperPrompt}
    help {helperPrompt}
    user {userAddDel}
    group {groupAddDel}
    admin {adminPriviledge}
}
