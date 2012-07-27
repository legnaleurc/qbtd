// Register form
$('#password2').blur( function(){
   if( $('#password').attr('value') !== $('#password2').attr('value') ){
      $('#pwd-group').addClass('error');
      $('#pwd-help').removeClass('hide');
   }else{
      $('#pwd-group').removeClass('error');
      $('#pwd-help').addClass('hide');
   }
});


$('#username').blur( function(){
   var username = $('#username').attr('value');
   if( username == '' ){
      checkStatReset('#username-group');
      checkError('#username-group', 'Username can not be empty');
   }else{
      checkStatReset('#username-group');

      $.ajax( {
         url: site_url + '/user/checkUsername/' + username,
         dataType: 'json',
         error: function(){ console.log('error'); },
         success: function(response){
            console.log('success');
            console.log('server response' + response);
            usernameCheck( response.found );
         }
      });
   }
});

function usernameCheck( found ){
   console.log('found = ' + found);
   if( found == false ){
      console.log('username not found');
      checkStatReset('#username-group');
      checkOkay('#username-group', 'OK!');

   }else if( found == true ){
      console.log('username found');
      checkStatReset('#username-group');
      checkError('#username-group', 'Username has been used');

   }else{
      // Hide status
      checkStatReset('#username-group');
   }
}

$('#email').blur( function(){
   var email = $('#email').attr('value');
   if( email == '' ){
      checkStatReset('#email-group');
      checkError('#email-group', 'Email can not be empty');
   }else{
      checkStatReset('#email-group');

      $.ajax( {
         url: site_url + '/user/checkemail/' + encodeURIComponent(email),
         dataType: 'json',
         error: function(){ console.log('error'); },
         success: function(response){
            console.log('success');
            console.log('server response' + response);
            emailCheck( response.found );
         }
      });
   }
});

function emailCheck( found ){
   console.log('found = ' + found);
   if( found == false ){
      console.log('email not found');
      checkStatReset('#email-group');
      checkOkay('#email-group', 'OK!');
   }else if( found == true ){
      console.log('email found');
      checkStatReset('#email-group');
      checkError('#email-group', 'Email has been used');
   }else{
      // Hide status
      console.log('hide message');
      checkStatReset('#email-group');
   }
}

function checkStatReset( groupId ){
   $( groupId ).removeClass('success');
   $( groupId ).removeClass('error');
   $( groupId + ' > div > span.help-inline' ).text('');
   $( groupId + ' > div > span.help-inline' ).addClass('hide');
}

function checkError( groupId, message ){
   checkStatReset( groupId );
   $( groupId ).addClass('error');
   $( groupId + ' > div > span.help-inline' ).text( message );
   $( groupId + ' > div > span.help-inline' ).removeClass('hide');
}

function checkOkay( groupId, message ){
   checkStatReset( groupId );
   $( groupId ).addClass('success');
   $( groupId + ' > div > span.help-inline' ).text( message );
   $( groupId + ' > div > span.help-inline' ).removeClass('hide');
}

// User search at admin panel
$('#username-key').keyup(  function(){
      var keyword = $('#username-key').attr('value');
      fetchUser( keyword );
});

function clearTable(){
   $('#user-list > tbody > tr').remove();
}

function fetchUser( keyword ){
   $.ajax( {
      url: site_url + '/admin/searchUser/' + encodeURIComponent( keyword ),
      dataType: 'json',
      error: function(){ console.log('error'); },
      success: function(response){
         renewTable( response );
      }
   });
}

function renewTable( list ){
   clearTable();
   for( index in list ){
      addRow( list[index] );
   }
}

function addRow( data ){
   $('#user-list > tbody ').append(
         '<tr> ' + 
            '<td>' + data.id + '</td>' +
            '<td>' + data.username + '</td>' +
            '<td>' + data.email + '</td>' +
            '<td>' +
               '<a href="' + site_url + '/admin/deleteUser/' + data.id + '" class="action-link">' +
               '<i class="icon-trash action-icon"></i> Delete </a>' +
               '<a href="#" class="action-link"><i class="icon-pencil action-icon"></i>Edit</a>' +
            '</td>' +
         '</tr>'
      );
}

// JSONP
