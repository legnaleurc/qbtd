<div class="navbar navbar-fixed-top">
   <div class="navbar-inner">
      <div class="container">
         <a class="brand" href="#">Qbtd</a>

<?php if( $loggedin == true ): ?>
            <ul class="nav pull-right" >
               <li><a href="#logout">Logout</a></li>
            </ul>

<?php else: ?>
            <ul class="nav pull-right" >
               <li><a href="#reg">Regieter</a></li>
               <li><a href="#login">Login</a></li>
            </ul>
<?php endif; ?>
      </div>
   </div>
</div>
