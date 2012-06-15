<div class="navbar navbar-fixed-top">
   <div class="navbar-inner">
      <div class="container">
      <a class="brand" href="<?php echo site_url(); ?>">Qbtd</a>

<?php if( $loggedin == true ): ?>
            <ul class="nav pull-right" >

            <?php if( $user['isAdmin'] == true): ?>
               <li><a href="<?php echo site_url('admin/'); ?>">User Management</a></li>
            <?php endif; ?>

               <li><a href="#">Upload Torrent</a></li>
               <li class="dropdown">
               <a href="#" class="dropdown-toggle" data-toggle="dropdown">
                  <i class="icon-user icon-white"></i>
                  Account
                  <i class="caret"></i>
                  </a>

                  <ul class="dropdown-menu">
                     <li><a href="<?php echo site_url('user/logout/'); ?>">Sign Out</a></li>
                  </ul>

               </li>
            </ul>

<?php else: ?>
            <ul class="nav pull-right" >
            <li><a href="<?php echo site_url('user/'); ?>">Regieter</a></li>
            <li><a href="<?php echo site_url('user/'); ?>">Login</a></li>
            </ul>
<?php endif; ?>
      </div>
   </div>
</div>
